// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter_Gunner.h"
#include "EnemyAIController_Gunner.h"
#include "EGSaveGame.h"
#include "EGGameInstance.h"
#include "EGPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimInstance_Gunner.h"
#include "Sound/SoundCue.h"
#include "Perception/AISenseConfig.h"

AEnemyCharacter_Gunner::AEnemyCharacter_Gunner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyAIController_Gunner::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SFX_Fire1 = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Fire1"));
	SFX_Fire2 = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Fire2"));
	SFX_Foot_L = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Foot_L"));
	SFX_Foot_R = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Foot_R"));
	MagComponent = CreateDefaultSubobject<UComponent_Mag>(TEXT("MagComponent"));
	StatComponent = CreateDefaultSubobject<UStatComponent_Gunner>(TEXT("StatComponent"));
	

	//	AiConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIConfigSight"));
	//WeaponMesh->SetupAttachment(GetMesh(), TEXT("GunPos"));
	
		SFX_Fire1->AttachToComponent(WeaponMesh,FAttachmentTransformRules::KeepRelativeTransform);
		SFX_Fire2->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);
		SFX_Foot_L->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);
		SFX_Foot_R->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);
	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;
	float X = 0.0f, Y = 0.0f, Z = 0.0f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_BODY(TEXT("SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_nathan_rigged_003_ue4/rp_nathan_rigged_003_ue4.rp_nathan_rigged_003_ue4'"));
	if (SM_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_BODY.Object);
		GetMesh()->SetRelativeLocation(FVector(X = 0.000000, Y = 0.000000, Z = -90.000000));
		GetMesh()->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = 270.000f, Roll = 0.000000f));
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Weapon(TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/SK_KA47_X.SK_KA47_X'"));
	if (SM_Weapon.Succeeded())
	{
		WeaponMesh->SetSkeletalMesh(SM_Weapon.Object);
		//WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("GunPos"));
		//WeaponMesh->SetupAttachment(GetMesh(), TEXT("GunPos"));
		//WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GunPos"));

	//	SFX_Fire1->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//	SFX_Fire2->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SFX_Fire1->SetupAttachment(WeaponMesh);
		SFX_Fire2->SetupAttachment(WeaponMesh);
		//WeaponMesh->AttachTo(GetMesh(), TEXT("GunPos"));
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance_Gunner>ANIM(TEXT("AnimBlueprint'/Game/MyFolder/AnimationBlueprint/Anim_Gunner.Anim_Gunner_C'"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue>SFX_Gun(TEXT("SoundCue'/Game/MyFolder/Sound/SE/AK47Que.AK47Que'"));
	if (SFX_Gun.Succeeded())
	{
		SFX_Fire1->Sound = SFX_Gun.Object;
		SFX_Fire2->Sound = SFX_Gun.Object;
		SFX_Fire1->bAutoActivate = false;
		SFX_Fire2->bAutoActivate = false;
	}
	
	static ConstructorHelpers::FObjectFinder<USoundAttenuation>SA_Gun(TEXT("SoundAttenuation'/Game/MyFolder/Sound/SE/Ak47Attenuation.Ak47Attenuation'"));
	if (SA_Gun.Succeeded())
	{
		SFX_Fire1->AttenuationSettings = SA_Gun.Object;
		SFX_Fire2->AttenuationSettings = SA_Gun.Object;
	
	}

	static ConstructorHelpers::FObjectFinder<USoundCue>SFX_FOOTr(TEXT("SoundCue'/Game/MyFolder/Sound/SE/Foot_right_Cue.Foot_right_Cue'"));
	if (SFX_FOOTr.Succeeded())
	{
		SFX_Foot_L->Sound = SFX_FOOTr.Object;
	
		SFX_Foot_L->bAutoActivate = false;
	
	}
	static ConstructorHelpers::FObjectFinder<USoundCue>SFX_FOOTl(TEXT("SoundCue'/Game/MyFolder/Sound/SE/Foot_left_Cue.Foot_left_Cue'"));
	if (SFX_FOOTl.Succeeded())
	{
		
		SFX_Foot_R->Sound = SFX_FOOTl.Object;
		
		SFX_Foot_R->bAutoActivate = false;
	}




	bCanFire = true;
	Cooltime = 0.0f;


	Point_Muzzle = FVector::ZeroVector;




	//setupPerception();
}
void  AEnemyCharacter_Gunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (bCanFire)
	{
		//EGLOG(Error, TEXT("Cooltime error"));
		return;
	}


	Cooltime += DeltaTime;
	if (Cooltime >= 0.1f)
	{
		bCanFire = true;
	
		Cooltime = 0.0f;

		//EGLOG(Warning, TEXT("Can fire"));	
	//tick 중단
		SetActorTickEnabled(false);
	}


}


void AEnemyCharacter_Gunner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
	


//	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this,&AEnemyCharacter_Gunner::perceptionUpdated);

}

void AEnemyCharacter_Gunner::BeginPlay()
{
	Super::BeginPlay();
	//if(WeaponMesh)
	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GunPos"));
	//EGLOG(Error, TEXT("Chara Begin"));

	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Gameinstance is nullptr"));
		return;
	}
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AEnemyCharacter_Gunner::LoadGame);
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AEnemyCharacter_Gunner::SaveGame);


	Anim = Cast<UAnimInstance_Gunner>(GetMesh()->GetAnimInstance());
	if (!Anim)EGLOG(Error, TEXT("********Anim Cast Failed********"));

	StatComponent->HPChangedDelegate.AddLambda([this]()->void {
		HPBar = Cast<UProgressBar>(HPBarWidget->GetUserWidgetObject()->GetWidgetFromName(TEXT("HPBar")));
		if (!HPBar)
		{
			EGLOG(Warning, TEXT(" HPBar Failed"));
			return;
		}
		HPBar->SetPercent(StatComponent->GetHPRatio());
		});

	StatComponent->HPZeroDelegate.AddLambda([this]()->void {
		//Anim Dead 설정
		//AIController 중단

		Anim->SetDead(true);
		auto AICon = Cast<AEnemyAIController_Gunner>(GetController());
		if (AICon)
		{
			AICon->StopAI();
		}


		});
}

void AEnemyCharacter_Gunner::BeginDestroy()
{
	Super::BeginDestroy();

}



void AEnemyCharacter_Gunner::SaveGame(UEGSaveGame * SaveInstance)
{
	Super::SaveGame(SaveInstance);
	if (!SaveInstance)
	{
		EGLOG(Error, TEXT("Save Instance is nullptr"));
		return;
	}

	auto SaveData = SaveInstance->D_Enemies.Find(GetOwner()->GetName());
	if (!SaveData)
	{
		EGLOG(Error, TEXT("Can't find %s's Data"), *GetOwner()->GetName());
		return;
	}
	//Hp저장
	StatComponent->SaveGame(SaveData);
	

}

void AEnemyCharacter_Gunner::LoadGame(const UEGSaveGame * LoadInstance)
{
	Super::LoadGame(LoadInstance);
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("LoadInstance is nullptr"));
		return;
	}
	auto LoadData = LoadInstance->D_Enemies.Find(GetOwner()->GetName());
	if (!LoadData)
	{
		EGLOG(Error, TEXT("LaodData FAILED"));
		return;
	}
	StatComponent->LoadGame(LoadData);
}

void  AEnemyCharacter_Gunner::initComponents()
{
	

	loadAssets();
}

void  AEnemyCharacter_Gunner::loadAssets()
{
	
}

void AEnemyCharacter_Gunner::playSFXGun()
{
	bool bTemp = UKismetMathLibrary::RandomBool();

	if (bTemp)
		SFX_Fire1->Play();
	else
		SFX_Fire2->Play();
}

//void AEnemyCharacter_Gunner::setupPerception()
//{
//	//UAISenseConfig AISenseConfig;
////	FAISenseID
//	//AIPerceptionComponent->ConfigureSense
//
//	//https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAISenseConfig_Sight/index.html
//	//UAISenseConfig_Sight Document
//	//UAISenseConfig_Sight senseConfig_Sight;
////	AiConfigSight->SightRadius = 1500.0f;
////	AiConfigSight->LoseSightRadius = 3100.0f;
////	AiConfigSight->PeripheralVisionAngleDegrees = 90.0f;
////	AiConfigSight->DetectionByAffiliation.bDetectEnemies = false;
////	AiConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
//
////	AIPerceptionComponent->ConfigureSense(*AiConfigSight);
////	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
//
//	
//
//
//}

void AEnemyCharacter_Gunner::Attack()
{

	if (!bCanFire)
	{
	//	EGLOG(Error, TEXT("Cant fire"));
		return;
	}

	//발사불가, Tick 활성화
	bCanFire = false;
	SetActorTickEnabled(true);
	//애니메이션과 소리 재생
	Anim->PlayFire(StatComponent->GetState());
	playSFXGun();
	//Mag에서 총 발사
	//Point_Muzzle =  WeaponMesh->GetSocketLocation(TEXT("Muzzle"));
	MagComponent->FireBullet(
		WeaponMesh->GetSocketLocation(TEXT("Muzzle")),
		WeaponMesh->GetComponentRotation(),
		WeaponMesh->GetForwardVector()
		);

}
void AEnemyCharacter_Gunner::Reload()
{
	Anim->PlayReload(StatComponent->GetState());


}
void AEnemyCharacter_Gunner::SetADS()
{
	StatComponent->SetState(EGunnerState::E_ADS);
	Anim->SetIronsights(true);

}
void AEnemyCharacter_Gunner::ReleaseADS()
{
	StatComponent->SetState(EGunnerState::E_Idle);
	Anim->SetIronsights(false);
}

float AEnemyCharacter_Gunner::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	StatComponent->TakeDamage(FinalDamage);

	//죽었다면 causer가 player인지 검사하고 경험치를 준다
	if (StatComponent->GetHPRatio() <= 0.0f)
	{
		auto player = Cast<AEGPlayerCharacter>(DamageCauser);
		if (player)
		{
			player->GetStatComponent()->GainExp(StatComponent->GetDropExp());
		}
		StatComponent->SetDamageable(false);
	}


	return FinalDamage;
}

void AEnemyCharacter_Gunner::PlaySFXFoot(bool bResult)
{
	if (bResult)
		SFX_Foot_R->Play();
	else
		SFX_Foot_L->Play();
}

