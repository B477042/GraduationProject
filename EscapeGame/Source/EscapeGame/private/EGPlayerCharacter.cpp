// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerCharacter.h"
#include "EGPlayerController.h"
#include "Item_Recover.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameWidget.h"
#include "Components/InputComponent.h"
#include "Projectile.h"
#include "GameSetting/public/EGCharacterSetting.h"
#include "Sound/SoundCue.h"
#include "SkillActor_ThunderType.h"
#include "Kismet/KismetMathLibrary.h"
#include "EGGameInstance.h"
#include "EGGameState.h"
#include "Item_CardKey.h"
#include "EGPostProcessVolume.h"
#include "MiniMapMarkerComponent.h"
#include "MiniMapTileManager.h"
#include "BarrierEffectComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Hearing.h"


// Sets default values
AEGPlayerCharacter::AEGPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitComponents();
	LoadAssets();
	SetupSpringArm();

	//object type을 PlayerCharacter로 해준다
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));
	//EGLOG(Warning, TEXT("Character Constroucter"));

	bSetMapArm = false;
	
	bIsGuarding = false;
	bIsDebugMode = false;
	

	MoveDirection = FVector::ZeroVector;
	CurrentVelocity = 78.f;
	
}

// Called when the game starts or when spawned
void AEGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	LoadHitEffects();
	EGLOG(Error, TEXT("Player Begin Play"));
	/*
	 * Inventory 관련 Delegate 등록
	 */
	/*auto PlayerCon = Cast<AEGPlayerController>(Controller);
	if(!PlayerCon)
	{
		EGLOG(Warning, TEXT("Casting Falied"));
		return;
		
	}*/
//================================================
//||		TimeLimit 관련 Delegate 등록			||
//================================================
	TimeLimitComponent->OnTimeOver.BindLambda([&]()->void {
		FDamageEvent DamageEvent;
		TakeDamage(10000.0f, DamageEvent, GetController(), this);
		//SetDeath();

		});


	
//================================================
//||			Stat 관련 Delegate 등록			||
//================================================

	Stat->HPZeroDelegate.AddUObject(this, &AEGPlayerCharacter::SetDeath);
	Stat->HPChangedDelegate.AddLambda([this]()->void {

		//현재 hp 비율을 GameInstance를 통해 postprocess로 넘겨줘서 피격효과가 나타나게 해준다.
		auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
		if (!GameInstance)return;

		if (GameInstance->GetPostProcessVolume().IsValid())
			GameInstance->GetPostProcessVolume()->SyncHpPercent(Stat->GetHPRatio());
	});

//================================================
//||		Montage 관련 Delegate Binding		||
//================================================
	//Anim->montage
//	Anim->OnMontageEnded.AddDynamic(this, &AEGPlayerCharacter::OnAttackMontageEnded);

	//montageStart
	Anim->OnMontageStarted.AddDynamic(this, &AEGPlayerCharacter::OnAttackMontageStart);
	//Motage End
	Anim->OnMontageEnded.AddDynamic(this, &AEGPlayerCharacter::OnAttackMontageEnded);

//=====================================================
//||GameState를 검사해서 이어하기/불러오기 처리합니다||
//=====================================================

	//GameInstance에서 GameState를 검사한다
	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Game Instance is not EGGameInstance"));
		return;
	}
	UEGSaveGame* LoadInstance = nullptr;
	
	switch (GameInstance->EGameState)
	{
	case EEGGameState::E_LoadGame:
		//Load Game Data
		 LoadInstance = Cast<UEGSaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->Name_SaveSlot0, GameInstance->GetSavedUserIndex()));
		if (!LoadInstance)
		{
			EGLOG(Error, TEXT("Load Insatnce Failed"));
			return;
		}
		//다른 오브젝트들에게 Load Game을 활성화 시킨다
		EGLOG(Error, TEXT("OnLoadGamePhase Delegate Broadcasted"));
		GameInstance->OnLoadGamePhaseDelegate.Broadcast(LoadInstance);

		//LoadGameData(LoadInstance);
		GameInstance->EGameState = EEGGameState::E_InPlay;
		break;
		//============================================================================================
	case EEGGameState::E_Death:

		LoadInstance = Cast<UEGSaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->Name_CheckPointSlot, GameInstance->GetSavedUserIndex()));
		if (!LoadInstance)
		{
			EGLOG(Error, TEXT("Load Insatnce Failed"));
			return;
		}

		//다른 오브젝트들에게 Load Game을 활성화 시킨다
		EGLOG(Error, TEXT("OnCheckPoint Delegate Broadcasted"));
		GameInstance->OnLoadGamePhaseDelegate.Broadcast(LoadInstance);

		//
		GameInstance->EGameState = EEGGameState::E_InPlay;

		break;
		//============================================================================================
	case EEGGameState::E_NextStage:

		LoadInstance = Cast<UEGSaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->Name_SaveSlot0, GameInstance->GetSavedUserIndex()));
		if (!LoadInstance)
		{
			EGLOG(Error, TEXT("Load Insatnce Failed"));
			return;
		}
		//Player의  스텟들만 불러온다
		OnNextStage(LoadInstance);

		//Game State 업데이트
		GameInstance->EGameState = EEGGameState::E_InPlay;
		break;
		//============================================================================================
	default:
		UE_LOG(LogTemp, Log, TEXT("New Game"));
		break;
	}

	//GameInstance의 Load Game Phase에 연동
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AEGPlayerCharacter::LoadGameData);

	


	DamagedPostEffect();
}

// Called every frame
void AEGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
	Move(DeltaTime);
}

// Called to bind functionality to input
void AEGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//axis input
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AEGPlayerCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AEGPlayerCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AEGPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AEGPlayerCharacter::Turn);
	
	//Action Input
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,this, &AEGPlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ComboAttack"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::ComboAttack);
	PlayerInputComponent->BindAction(TEXT("ChargeAttack"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::ChargeAttack);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::StartRunning);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &AEGPlayerCharacter::StopRunning);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Repeat, this, &AEGPlayerCharacter::UsingStaminaTick);
	PlayerInputComponent->BindAction(TEXT("Roll"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::Roll);
	PlayerInputComponent->BindAction(TEXT("Recovery"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::UseRecoveryItem);
	PlayerInputComponent->BindAction(TEXT("ToggleMap"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::ToggleMap);
	PlayerInputComponent->BindAction(TEXT("Guard"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::PressGuard);
	PlayerInputComponent->BindAction(TEXT("Guard"), EInputEvent::IE_Released, this, &AEGPlayerCharacter::ReleaseGuard);
	PlayerInputComponent->BindAction(TEXT("Guard"), EInputEvent::IE_Repeat, this, &AEGPlayerCharacter::UsingStaminaTick);
	PlayerInputComponent->BindAction(TEXT("Fury"), EInputEvent::IE_Pressed, this, &AEGPlayerCharacter::PressFury);

	EGLOG(Warning, TEXT("Player input component"));
}

void AEGPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EGLOG(Warning, TEXT("Player Post init compons"));


	//Anim Instance에 빨리 접근하기 위해
	Anim = Cast<UAnim_Player>(GetMesh()->GetAnimInstance());
	if (!Anim)
	{
		EGLOG(Error, TEXT("AnimInstance is not UAnim_Player"));
		return;
	}

	
	//발소리 소음 이벤트
	Anim->OnPlant.BindUObject(this, &AEGPlayerCharacter::OnMakeNoiseEvenet);


	//Weapon Hit 판정
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEGPlayerCharacter::OnWeaponBeginOverlap);

	
	
	//Stat->SetSpeedLimits( MaxWalkingSpeed, MinWalkingSpeed, MaxRunningSpeed);


}


float AEGPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	

	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	
	/*if (bCanBeDamaged == false)
	{
		EGLOG(Error, TEXT("Can't Take Damage"));
		return 0.0f;
	}*/

	if(bIsGuarding)
	{
		return ReflectProjectiles(DamageCauser,FinalDamage);
		
	}



	Anim->TakeDamage(DamageCauser);
	Stat->TakeDamage(FinalDamage);
	FuryComponent->TakeDamage(FinalDamage);

	return FinalDamage;
}


void AEGPlayerCharacter::HealHP(float addHP)
{
	Stat->HealHP(addHP);
}

UStatComponent_Player* AEGPlayerCharacter::GetStatComponent()const
{
	return Stat;
}

UComponent_Inventory * AEGPlayerCharacter::GetInventory()const
{
	return Inventory;
}

UComponent_Fury* AEGPlayerCharacter::GetFuryComponent()const
{
	return FuryComponent;
}

UComponent_TimeLimit* AEGPlayerCharacter::GetTimeLimitComponent() const
{
	return TimeLimitComponent;
}

void AEGPlayerCharacter::ChargeAttack()
{
	if (bResticLMBInput)
	{
		
		return;
	}

	//Charge Attack은 시동이 걸린 상태에서만 실행될 것이다
	if (!Stat->IsAttacking())
	{ 
		return; 
	}


	Anim->PlaySkillMontage(Stat->GetCurrentCombo());
	
	
	
	
		
}

void AEGPlayerCharacter::ComboAttack()
{
	//입력 제한 확인
	if (bResticLMBInput)
	{
		return;
	}


	if (GetCharacterMovement()->IsFalling())
	{
		
		AirAttack();
		return;
	}
	
	//시동동작
	if (!Stat->IsAttacking())
	{
		Stat->SetComboStartState();
		//EGLOG(Warning, TEXT("Current Comobo : %d"), Stat->GetCurrentCombo());
		Anim->JumpToComboAttackSection(Stat->GetCurrentCombo());
		Anim->PlayAttackMontage();//시동이니 ComboAttack1이 재생된다
		//Stat->OnAttacking(true);
		
	}
	//이미 공격중인 상태
	else
	{
		//combo Attack input이 걸렸는지 확인한다.
		//input이 안 걸렸다면 걸어준다
		if (!Stat->CheckCanComboAttack())
		{
			
			Stat->SetComboAttackInput(true);//다음 몽타쥬가 재생될 수 있게 해준다
			Stat->SetChargeAttackInput(false);//대신 차지 공격은 불가능하다
		}
	}
	EGLOG(Error, TEXT("Current Combo : %d"), Stat->GetCurrentCombo());
	
}

void AEGPlayerCharacter::AirAttack()
{
	//한가지 동작만 반복될 것이다
	if (!Stat->IsAttacking())
	{
		Stat->SetComboStartState();
		Anim->PlayAirAttackMontage();
	}
	

}

void AEGPlayerCharacter::SlashAttack()
{
	//Box Scan
	//Hit All scanned actor
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Warning, TEXT("World is invalid"));
		return;
	}
	FVector Start = GetActorLocation();
	FVector End = 200.0f * GetActorForwardVector() + Start;
	FVector HalfSize = FVector(100, 100, 100);
	FRotator Orientation = GetActorRotation();

	TArray<AActor*> Ignores;
	TArray<FHitResult>HitResult;
	bool bResult = UKismetSystemLibrary::BoxTraceMultiByProfile(World,Start,End,HalfSize,Orientation,TEXT("PlayerWeapon"),false, Ignores,EDrawDebugTrace::None,HitResult,true);
	if (!bResult)
	{
		EGLOG(Log, TEXT("NO hit"));
		return;
	}
	//Find Enemy Character Types
	for (auto it : HitResult)
	{
		auto TargetActor = Cast<AEnemyCharacter>(it.Actor);
		if (!TargetActor)
		{
			EGLOG(Log, TEXT("Not Enemy Character types"));
			continue;
		}
		FDamageEvent DamageEvent;

		TargetActor->TakeDamage(75, DamageEvent, GetController(), this);
		Container_Hit->ActivateEffectAt(TargetActor->GetActorLocation());

	}


}

void AEGPlayerCharacter::StartRunning()
{
//	EGLOG(Warning, TEXT("Run Key Preesed"));

	//if (GetCharacterMovement()->GetCurrentAcceleration() == FVector::ZeroVector)return;
	//Stat->SetRunning();//달릴 상태로 만들어 준다
	//
	if (Stat->IsAttacking())return;

	if (Stat->CanUseStamina())
	{
		Stat->SetStaminaUsing(true);
		Anim->SetJogPlayRate(true);
		GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	}


}

//호출 시점 IE_Repeated
//누르고 있는지 좀 돼야 반응한다
//스테미나를 사용하는 기능에서 호출됩니다. 달리기/막기
void AEGPlayerCharacter::UsingStaminaTick()
{
	
	if (!Stat->CanUseStamina())
	{
		StopRunning();
		ReleaseGuard();
	}
	else
	{
		//EGLOG(Warning, TEXT("Using Stamina"));
		Stat->UseStaminaTick(GetWorld()->DeltaTimeSeconds);
	}

}
//호출시점IE_Released
//키에서 때면 바로 호출된다
void AEGPlayerCharacter::StopRunning()
{
	/*EGLOG(Warning, TEXT("Run Key Released"));*/
	Stat->SetStaminaUsing(false);
	Anim->SetJogPlayRate(false);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	/*if (GetCharacterMovement()->GetCurrentAcceleration() == FVector::ZeroVector)return;
	Stat->SetWalking();*/
}



void AEGPlayerCharacter::Roll()
{
	//Anim의 bIsRolling을 true로 바꿔주면 AnimBP에서 구르는 애니메이션을 재생하게 된다.
	Anim->SetRolling(true);
	
	

}
//회복 아이템을 사용한다. 기본적으로 키를 입력하면 호출된다. 강제로 사용하게 만드는 방법도 만들 수 있을 것 같다
void AEGPlayerCharacter::UseRecoveryItem()
{
	Inventory->UseItem(AItem_Recover::Tag,this);
	
}

//mini map Spring arm.의 길이를 조절한다
void AEGPlayerCharacter::ToggleMap()
{
	
	if (bSetMapArm==false)
	{
		MiniMapArm->TargetArmLength=POS_Minimap.Z+ maxMiniMapArmLength;
		EGLOG(Log, TEXT("Change To Max"));
		bSetMapArm = true;
		return;
	}
	if (bSetMapArm==true)
	{
		
		MiniMapArm->TargetArmLength = POS_Minimap.Z + minMiniMapArmLength;
		bSetMapArm = false;
		EGLOG(Log, TEXT("Change To Min"));
		return;
	}
	else
	{
		EGLOG(Error, TEXT("Minimap Toggle Error"));
	}
}

void AEGPlayerCharacter::PressGuard()
{

	if (Stat->CanUseStamina())
	{
		BarrierEffect->ActivateEffect(GetActorLocation());
		Stat->SetStaminaUsing(true);
		
		Stat->SetDamageable(false);
		Stat->SetDontMove();
	//GetCharacterMovement()
	//RestricInput();
	
		Anim->SetGuarding(true);
		bIsGuarding = true;

	}

	

}

void AEGPlayerCharacter::ReleaseGuard()
{
	BarrierEffect->DeactivateEffect();
	Stat->SetDamageable(true);
	Stat->SetWalking();
	
	//RecoverInput();
	Anim->SetGuarding(false);
	bIsGuarding = false;
}


void AEGPlayerCharacter::ActiveThunder()
{
	Skill_Thunder->UseSkill(GetActorLocation());
}

void AEGPlayerCharacter::RestricInput(const ERestricInputType& Type)
{
	switch(Type)
	{
	case ERestricInputType::E_AxisMoving:
		bRestricAxisInput = true;
		break;
	case ERestricInputType::E_LMB:
		bResticLMBInput = true;
		break;
	case ERestricInputType::E_RMB:
		bRestricRMBInput = true;
		break;
	case ERestricInputType::E_LRMB:
		bResticLMBInput = true;
		bRestricRMBInput = true;
		break;
	default:
		EGLOG(Log, TEXT("None"));
	}

	
	
}

void AEGPlayerCharacter::RecoverInput(const ERestricInputType& Type)
{
	switch (Type)
	{
	case ERestricInputType::E_AxisMoving:
		bRestricAxisInput = false;
		break;
	case ERestricInputType::E_LMB:
		bResticLMBInput = false;
		break;
	case ERestricInputType::E_RMB:
		bRestricRMBInput = false;
		break;
	case ERestricInputType::E_LRMB:
		bRestricRMBInput = false;
		bResticLMBInput = false;
		break;
	default:
		EGLOG(Log, TEXT("None"));
	}
 
}










void AEGPlayerCharacter::InitComponents()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	MiniMapArm= CreateDefaultSubobject<USpringArmComponent>(TEXT("MINMAPARM"));
	MapRenderer = CreateDefaultSubobject<UMiniMapRenderComponent>(TEXT("MAPRENDERER"));
	Stat = CreateDefaultSubobject <UStatComponent_Player>(TEXT("STAT"));
	
	Inventory = CreateDefaultSubobject<UComponent_Inventory>(TEXT("INVENTORY"));
	SwordEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Sword"));
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	Container_Hit=CreateDefaultSubobject < USkillContainer_PlayerHitEffect>(TEXT("HitEffects"));
	AttackSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSound"));
	MiniMapMarkerComponent = CreateDefaultSubobject<UMiniMapMarkerComponent>(TEXT("MiniMapMarker"));
	BarrierEffect = CreateDefaultSubobject<UBarrierEffectComponent>(TEXT("BarrierEffectComponent"));
	FuryComponent = CreateDefaultSubobject<UComponent_Fury>(TEXT("FuryComponent"));
	AIPerceptionStimuliSource = CreateDefaultSubobject< UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSource"));
	TimeLimitComponent = CreateDefaultSubobject<UComponent_TimeLimit>(TEXT("TimeLimitComponent"));

	//====================================================================================================
	//Components Tree
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	MiniMapArm->SetupAttachment(GetCapsuleComponent());
	MapRenderer->SetupAttachment(MiniMapArm);
	WeaponCollision->SetupAttachment(SwordEffect);
	AttackSound->SetupAttachment(RootComponent);
	MiniMapMarkerComponent->SetupAttachment(RootComponent);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	//====================================================================================================
	//미니맵 및 카메라 관련 초기값 설정
	minMiniMapArmLength = POS_Minimap.Z + 3000.0f;
	maxMiniMapArmLength = POS_Minimap.Z + 7000.0f;
	
	float X=0, Y=0, Z=0,Pitch=0,Yaw=0,Roll=0;
	Camera->SetRelativeLocation(FVector(0.0f, 30.0f, 90.0f));
	SpringArm->TargetArmLength = 500.0f;

	MiniMapArm->TargetArmLength = POS_Minimap.Z+minMiniMapArmLength;
	MiniMapArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f));
	 
	MiniMapArm->bDoCollisionTest = false;

	//마커 초기값 설정
	MiniMapMarkerComponent->SetRelativeLocation(FVector(0, 0, POS_Minimap.Z));
	MiniMapMarkerComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	
	//무기 설정
	WeaponCollision->SetRelativeLocationAndRotation(FVector(X = 0.976299f, Y = 1.777855f, Z = 66.010002f), FRotator(Pitch = -1.184324, Yaw = 155.845551, Roll = 0.682941));
	 
	WeaponCollision->SetBoxExtent(FVector(X = 9.093354, Y = 6.199887, Z = 63.501183));
	WeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));

	//스프링암 값 설정
	SetupSpringArm();
	
	
	//====================================================================================================
	//AIPerceptionStimuliSource
	AIPerceptionStimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
	AIPerceptionStimuliSource->RegisterForSense(UAISense_Hearing::StaticClass());

}

void AEGPlayerCharacter::LoadAssets()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_CHARACTER(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/KwangSunrise.KwangSunrise"));
	if (SM_CHARACTER.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_CHARACTER.Object);
	}



	///Game/MyFolder/AnimationBlueprint/AniPlayerCharacterKwang.AniPlayerCharacterKwang
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);


	static ConstructorHelpers::FClassFinder<UAnimInstance>ANI_CHARACTER(TEXT("AnimBlueprint'/Game/MyFolder/AnimationBlueprint/AniPlayerCharacterKwang.AniPlayerCharacterKwang_C'"));
	if (ANI_CHARACTER.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANI_CHARACTER.Class);
	}

	
	//ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/Sword/FX/P_Kwang_Sword_Bolts.P_Kwang_Sword_Bolts'
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_SwordBolt(TEXT("ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/Sword/FX/P_Kwang_Sword_Bolts.P_Kwang_Sword_Bolts'"));
	if (PS_SwordBolt.Succeeded())
	{
		SwordEffect->SetTemplate(PS_SwordBolt.Object);
		if (GetMesh()->DoesSocketExist(TEXT("FX_weapon_base")))
		{
			SwordEffect->SetupAttachment(GetMesh(), TEXT("FX_weapon_base"));
		}
	}

	//SoundCue'/Game/ParagonKwang/Characters/Heroes/Kwang/Sounds/SoundCues/Kwang_Effort_Attack.Kwang_Effort_Attack'

	static ConstructorHelpers::FObjectFinder<USoundCue>SC_Attack(TEXT("SoundCue'/Game/MyFolder/Sound/Voice/Kwang_Effort_Attack.Kwang_Effort_Attack'"));
	if (SC_Attack.Succeeded())
	{
		AttackSound->SetSound(SC_Attack.Object);
		AttackSound->bAutoActivate = false;
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_Marker(TEXT("MaterialInstanceConstant'/Game/MyFolder/My_Material/MaterialInstance/MI_Marker_Player.MI_Marker_Player'"));
	if(MI_Marker.Succeeded())
	{
		MiniMapMarkerComponent->SetMaterial(0, MI_Marker.Object);
	}

}


void AEGPlayerCharacter::SetupSpringArm()
{
	//ĳ���Ϳ� �Ÿ�
	ArmLengthTo = 600.0f;
	SpringArm->SetRelativeRotation(FRotator(-65.667404f, -9.943956f, 0.771690f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	

	////ArmLengthTo = 420.0f;

	MiniMapArm->bUsePawnControlRotation = false;
	MiniMapArm->bInheritPitch = false;
	MiniMapArm->bInheritRoll = false;
	MiniMapArm->bInheritYaw = false;

}



void AEGPlayerCharacter::UpDown( float  NewAxisValue)
{
 
	if (NewAxisValue == 0.0f)return;
	if (bRestricAxisInput)return;

		
	////양수면 앞, 음수면 뒤
	


	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);
		
}

void AEGPlayerCharacter::LeftRight( float NewAxisValue)
{
	
	if (NewAxisValue == 0.0f)return;
	if (bRestricAxisInput)return;
 
	
	////양수면 오른쪽, 음수면 왼쪽
	
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);

}

void AEGPlayerCharacter::LookUp(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)return;
	   
	AddControllerPitchInput(NewAxisValue);
	
}

void AEGPlayerCharacter::Turn( float  NewAxisValue)
{
	if (NewAxisValue == 0.0f)return;
	AddControllerYawInput(NewAxisValue);
}

void AEGPlayerCharacter::Jump()
{
	if(!Stat->IsAttacking())
	Super::Jump();
	
	
}

void AEGPlayerCharacter::KeyInputTest()
{
	//playerinputcomponent
	
		
}

void AEGPlayerCharacter::SetDeath()
{
	//디버깅 모드라면 죽지 않는다
	if (bIsDebugMode)return;
	
	//Anim->StopAllMontages(0.0f);

	Anim->SetDead();
	RestricInput(ERestricInputType::E_AxisMoving);
	RestricInput(ERestricInputType::E_LRMB);
	auto EGGameInstance = Cast<UEGGameInstance>(GetGameInstance());
	if (!EGGameInstance)
	{
		return;
	}
	EGGameInstance->EGameState = EEGGameState::E_Death;


}

void AEGPlayerCharacter::Move(float DeltaTime)
{
	if (MoveDirection.IsZero()) {
		return;
	}

	MoveDirection.Normalize();
	AddMovementInput(MoveDirection, CurrentVelocity * DeltaTime);
	MoveDirection.Set(0.0f, 0.0f, 0.0f);
}

void AEGPlayerCharacter::PressFury()
{
	if (!FuryComponent->UseFury())
	{
		return;

	}
	
	UE_LOG(LogTemp, Log, TEXT("Fury used"));


}

void AEGPlayerCharacter::OnMakeNoiseEvenet()
{
	UAISense_Hearing::ReportNoiseEvent(this,GetActorLocation(),
		1.0f,this,200.0f,TEXT("Player"));

	//EGLOG(Log, TEXT("tep"));
}

float AEGPlayerCharacter::ReflectProjectiles(AActor* DamageCauser, float FinalDamage)
{

	//Projectile Type Only
	const auto Projectile = Cast<AProjectile>(DamageCauser);
	if (Projectile)
	{
		//투사체 반사
		if (bIsGuarding)
		{

			Projectile->Reflected();
			
		}

	

	}
	return FinalDamage;
	
}

//Player가 아닌 모든 것에 Take Damage를 일으킵니다
void AEGPlayerCharacter::OnWeaponBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto target = Cast<AEGPlayerCharacter>(OtherActor);
	if (target) { 
		EGLOG(Error, TEXT("that's player character"));
		return; }
	FDamageEvent DamageEvent;
	EGLOG(Error, TEXT("Hit : %s"), *OtherActor->GetName());
	OtherActor->TakeDamage(Stat->GetATK(),DamageEvent,Controller,this );

	Container_Hit->ActivateEffectAt(OtherActor->GetActorLocation());
}

void AEGPlayerCharacter::OnCheckCanComboAttack(UAnimMontage* Montage, bool bInterrupted)
{
	if (Stat->CheckCanComboAttack())
	{
		//EGLOG(Error, TEXT("lambda check combo"));
		//AnimNotify_CanComboAttack 에서 호출될 함수다
		Stat->SetComboStartState();
		Anim->JumpToComboAttackSection(Stat->GetCurrentCombo());
		//Anim->Montage->Play();
	}
}
void AEGPlayerCharacter::OnAttackMontageStart(UAnimMontage* Montage)
{
	WeaponCollision->SetCollisionProfileName("PlayerWeapon");
}


void AEGPlayerCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	//if (!Stat->IsAttacking())return;
	//EGLOG(Warning, TEXT("PlayEnded"));
	WeaponCollision->SetCollisionProfileName("NoCollision");

	ComboAttackEnd();
}

void AEGPlayerCharacter::ComboAttackStart()
{
	if (Stat == nullptr)return;
	Stat->SetComboStartState();
}


void AEGPlayerCharacter::ComboAttackEnd()
{
	if (Stat == nullptr)return;
	Stat->SetComboEndState();
}

//미사용, 데미지를 준 엑터와 플레이어의 각도 계산
FName AEGPlayerCharacter::CalcHitDirection(AActor * DamageCauser)
{
	FName Result;

	FVector F_Player = GetActorForwardVector();
	FVector F_Causer = DamageCauser->GetActorForwardVector();

	FVector2D F2_Player = FVector2D(F_Player.X, F_Player.Y);
	FVector2D F2_Causer = FVector2D(F_Causer.X, F_Causer.Y);

	

	float Dot2D = UKismetMathLibrary::DotProduct2D(F2_Player, F2_Causer);
	float Angle = UKismetMathLibrary::Acos(Dot2D);

	Angle = UKismetMathLibrary::Abs(Angle);

	if (Angle < 90.0f)Result = TEXT("React_Fwd");
	else Result = TEXT("React_Bwd");


	return Result;
}

// PostProcess 연동 테스트
void AEGPlayerCharacter::DamagedPostEffect()
{
	FPostProcessSettings& PostProcessSettings = Camera->PostProcessSettings;

	PostProcessSettings.ColorGamma = FVector4(1.0f, 1.0f, 1.0f, 0.0f);
}

// 스킬 이펙트를 생성하고 스킬 컨테이너 컴포넌트에 넣어줍니다.
void AEGPlayerCharacter::LoadHitEffects()
{
	if (!GetWorld()) { EGLOG(Warning, TEXT("No0 world")); return; }
	int cap = Container_Hit->GetCapacity();
	for(int i=0;i<cap;i++)
		Container_Hit->AddSkillObj( GetWorld()->SpawnActor<ASkillActor_Hit>());

	Skill_Thunder = GetWorld()->SpawnActor < ASkillActor_ThunderType>();

}

void AEGPlayerCharacter::LoadGameData(const UEGSaveGame* LoadInstance)
{
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("LoadInstance is nullptr"));
		return;
	}


	auto PlayerData = LoadInstance->D_Player;
	


	//좌표와 스텟을 불러온다
	SetActorLocationAndRotation(PlayerData.Location, PlayerData.Rotation);
	Stat->LoadGameStat(PlayerData.Level, PlayerData.Exp, PlayerData.Hp);

	//Load CardKeys
	if (PlayerData.n_CardKeys > 0)
	{
		auto newItem = GetWorld()->SpawnActor<AItem_CardKey>();

		if (!newItem)
		{
			EGLOG(Error, TEXT("Item Casting Failed"));
			return;
		}
		Inventory->LoadGameData(newItem, PlayerData.n_CardKeys);
	}

	if (PlayerData.n_RecoverItmes > 0)
	{
		auto newItem = GetWorld()->SpawnActor<AItem_Recover>();

		if (!newItem)
		{
			EGLOG(Error, TEXT("Item Casting Failed"));
			return;
		}
		//인벤토리에 등록해주고 Tag에 Spawned를 추가시켜 준다
		Inventory->LoadGameData(newItem, PlayerData.n_RecoverItmes);
		newItem->Tags.Add(TSpawned);
		EGLOG(Warning, TEXT("This Item is Spawned. %s"), *newItem->GetName());
	}



}

void AEGPlayerCharacter::OnNextStage(const UEGSaveGame * LoadInstance)
{
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("LoadInstance is nullptr"));
		return;
	}


	auto PlayerData = LoadInstance->D_Player;

	//Stat을 불러온다
	Stat->LoadGameStat(PlayerData.Level, PlayerData.Exp, PlayerData.Hp);


	//이전 스테이지에서 획득한 아이템들을 불러온다
	if (PlayerData.n_CardKeys > 0)
	{
		auto newItem = GetWorld()->SpawnActor<AItem_CardKey>();

		if (!newItem)
		{
			EGLOG(Error, TEXT("Item Casting Failed"));
			return;
		}
		Inventory->LoadGameData(newItem, PlayerData.n_CardKeys);
	}

	if (PlayerData.n_RecoverItmes > 0)
	{
		auto newItem = GetWorld()->SpawnActor<AItem_Recover>();

		if (!newItem)
		{
			EGLOG(Error, TEXT("Item Casting Failed"));
			return;
		}
		//인벤토리에 등록해주고 Tag에 Spawned를 추가시켜 준다
		Inventory->LoadGameData(newItem, PlayerData.n_RecoverItmes);
		newItem->Tags.Add(TSpawned);
		EGLOG(Warning, TEXT("This Item is Spawned. %s"), *newItem->GetName());
	}


}
