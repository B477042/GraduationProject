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
	auto PlayerCon = Cast<AEGPlayerController>(Controller);
	if(!PlayerCon)
	{
		EGLOG(Warning, TEXT("Casting Falied"));
		return;
		
	}
	
	
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

	//Load Game일 경우 처리
	if (GameInstance->EGameState == EEGGameState::E_LoadGame)
	{

		//Load Game Data
		auto LoadInstance = Cast<UEGSaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->GetSaveSlotName(), GameInstance->GetSavedUserIndex()));
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

	}
	//이어하기
	else if (GameInstance->EGameState == EEGGameState::E_NextStage)
	{
		auto LoadInstance = Cast<UEGSaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->GetSaveSlotName(), GameInstance->GetSavedUserIndex()));
		if (!LoadInstance)
		{
			EGLOG(Error, TEXT("Load Insatnce Failed"));
			return;
		}
		//Player의  스텟들만 불러온다
		OnNextStage(LoadInstance);

		//Game State 업데이트
		GameInstance->EGameState = EEGGameState::E_InPlay;

	}

	else
		EGLOG(Warning, TEXT("NewGame"));
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
	



	//Weapon Hit 판정
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEGPlayerCharacter::OnWeaponBeginOverlap);

	
	
	//Stat->SetSpeedLimits( MaxWalkingSpeed, MinWalkingSpeed, MaxRunningSpeed);


}


float AEGPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	

	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//bCanBeDamaged가 0이라면 데미지를 받지 않는다
	
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

	return FinalDamage;
}


void AEGPlayerCharacter::HealHP(float addHP)
{
	Stat->HealHP(addHP);
}

UStatComponent_Player* AEGPlayerCharacter::GetStatComponent()
{
	return Stat;
}

UComponent_Inventory * AEGPlayerCharacter::GetInventory()
{
	return Inventory;
}

void AEGPlayerCharacter::ChargeAttack()
{
	//Charge Attack은 시동이 걸린 상태에서만 실행될 것이다
	if (!Stat->IsAttacking())return;

	Anim->PlaySkillMontage(Stat->GetCurrentCombo());
	
	
	
	
		
}

void AEGPlayerCharacter::ComboAttack()
{
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

void AEGPlayerCharacter::StartRunning()
{
	EGLOG(Warning, TEXT("Run Key Preesed"));

	//if (GetCharacterMovement()->GetCurrentAcceleration() == FVector::ZeroVector)return;
	//Stat->SetRunning();//달릴 상태로 만들어 준다
	//
	if (Stat->IsAttacking())return;

	if (Stat->CanUseStamina())
	{
		Stat->SetStaminaUsing(true);
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
		Stat->UseStamina(GetWorld()->DeltaTimeSeconds);
	}

}
//호출시점IE_Released
//키에서 때면 바로 호출된다
void AEGPlayerCharacter::StopRunning()
{
	EGLOG(Warning, TEXT("Run Key Released"));
	Stat->SetStaminaUsing(false);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	/*if (GetCharacterMovement()->GetCurrentAcceleration() == FVector::ZeroVector)return;
	Stat->SetWalking();*/
}


/*
	호출시점 : Shift + Space
	구르는 동작을 시작한다
	구르기 시작하는 과정이 여기에 들어간다

	
*/
void AEGPlayerCharacter::Roll()
{
	//Anim의 bIsRolling을 true로 바꿔주면 AnimBP에서 구르는 애니메이션을 재생하게 된다.
	Anim->SetRolling(true);
	float interval = Anim->GetRollingLength();

	//Actor를 뒤로 후퇴시킬 방향
	FVector jumpPoint = GetActorForwardVector()*interval;

	//입력을 제한 시킨다
	RestricInput();

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
		MiniMapArm->SetRelativeLocation(FVector(0.0f, 0.0f, maxMiniMapArmLength));
		EGLOG(Error, TEXT("Change To Max"));
		bSetMapArm = true;
		return;
	}
	if (bSetMapArm==true)
	{
		MiniMapArm->SetRelativeLocation(FVector(0.0f, 0.0f, minMiniMapArmLength));
		bSetMapArm = false;
		EGLOG(Error, TEXT("Change To Min"));
		return;
	}
	else
	{
		EGLOG(Error, TEXT("Error"));
	}
}

void AEGPlayerCharacter::PressGuard()
{

	if (Stat->CanUseStamina())
	{
		EGLOG(Error, TEXT("Guard start"));
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
	
	EGLOG(Error, TEXT("Guard Release"));
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

void AEGPlayerCharacter::RestricInput()
{
	auto myCon = Cast<APlayerController>(GetController());
	if (myCon != nullptr)
	{
		
		DisableInput(myCon);
	}
}

void AEGPlayerCharacter::RecoverInput()
{
	auto myCon = Cast<APlayerController>(GetController());
	if (myCon != nullptr)
	{
		EnableInput(myCon);
	}
}










void AEGPlayerCharacter::InitComponents()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	MiniMapArm= CreateDefaultSubobject<USpringArmComponent>(TEXT("MINMAPARM"));
	MapRenderer = CreateDefaultSubobject<UMiniMapRenderComponent>(TEXT("MAPRENDERER"));
	Stat = CreateDefaultSubobject <UStatComponent_Player>(TEXT("STAT"));
	SelfDamage = CreateDefaultSubobject<UComponent_SelfDamage>(TEXT("SelfDAMAGE"));
	Inventory = CreateDefaultSubobject<UComponent_Inventory>(TEXT("INVENTORY"));
	SwordEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Sword"));
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	Container_Hit=CreateDefaultSubobject < USkillContainer_PlayerHitEffect>(TEXT("HitEffects"));
	AttackSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSound"));
	MiniMapMarkerComponent = CreateDefaultSubobject<UMiniMapMarkerComponent>(TEXT("MiniMapMarker"));

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
	minMiniMapArmLength = POS_Minimap.Z + 1500.0f;
	maxMiniMapArmLength = POS_Minimap.Z + 3000.0f;
	
	float X=0, Y=0, Z=0,Pitch=0,Yaw=0,Roll=0;
	Camera->SetRelativeLocation(FVector(0.0f, 30.0f, 90.0f));
	SpringArm->TargetArmLength = 500.0f;

	MiniMapArm->TargetArmLength = 0.0f;
	MiniMapArm->SetRelativeLocation(FVector(0.0f, 0.0f, POS_Minimap.Z+1500.0f));
	MiniMapArm->SetRelativeRotation(FRotator(-90.0f, 0.0f,0.0f));

	//마커 초기값 설정
	MiniMapMarkerComponent->SetRelativeLocation(FVector(0, 0, POS_Minimap.Z));
	MiniMapMarkerComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	
	//무기 설정
	WeaponCollision->SetRelativeLocation(FVector(X = 0.976299f, Y = 1.777855f, Z = 66.010002f));
	WeaponCollision->SetRelativeRotation(FRotator(Pitch = -1.184324, Yaw = 155.845551, Roll = 0.682941));
	WeaponCollision->SetBoxExtent(FVector(X = 9.093354, Y = 6.199887, Z = 63.501183));
	WeaponCollision->SetCollisionProfileName(TEXT("NoCollision"));

	//스프링암 값 설정
	SetupSpringArm();
	
	
	////포스트 프로세스 값 지정
	//FPostProcessSettings& PostProcessSettings = Camera->PostProcessSettings;

	//



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
	 
		//AddMovementInput(GetActorForwardVector(), NewAxisValue);
		//진행방향으로 캐릭터를 돌리는 방식
		//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);

		////양수면 앞, 음수면 뒤
	


	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);
		
}

void AEGPlayerCharacter::LeftRight( float NewAxisValue)
{
	
	if (NewAxisValue == 0.0f)return;
 
	//진행방향으로 캐릭터를 돌리는 방식
	//AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
	//EGLOG(Warning, TEXT("Left or Right Pressed"));
	
	////양수면 오른쪽, 음수면 왼쪽
	
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);

}

void AEGPlayerCharacter::LookUp(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)return;
	/*if (GetVelocity() == FVector::ZeroVector)
	{
		auto CurrentControllerPitch = GetControlRotation().Pitch;
		if (CurrentControllerPitch + NewAxisValue >= 30.0f)
			NewAxisValue = -CurrentControllerPitch + 30.0f;
		else if(CurrentControllerPitch + NewAxisValue <= -30.0f)
			NewAxisValue = -CurrentControllerPitch - 30.0f;
	}*/
	/*if (GetCharacterMovement()->IsWalking())
		EGLOG(Warning, TEXT("Walk!"));*/
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
	
	Anim->SetDead();
	RestricInput();
	Anim->Montage_Stop(0.0f);



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

	Container_Hit->SetEffectAt(OtherActor->GetActorLocation());
}

void AEGPlayerCharacter::OnCheckCanComboAttack(UAnimMontage* Montage, bool bInterrupted)
{
	if (Stat->CheckCanComboAttack())
	{
		EGLOG(Error, TEXT("lambda check combo"));
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
