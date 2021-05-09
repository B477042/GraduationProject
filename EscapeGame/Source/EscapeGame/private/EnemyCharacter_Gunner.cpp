// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter_Gunner.h"
#include "EnemyAIController_Gunner.h"
#include "EGSaveGame.h"
#include "EGGameInstance.h"
#include "EGPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimInstance_Gunner.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"

//UAIPerceptionComponent
//https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAIPerceptionComponent/index.html

//UAISenseConfig_Sight
//https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAISenseConfig_Sight/index.html


AEnemyCharacter_Gunner::AEnemyCharacter_Gunner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyAIController_Gunner::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	FireSound1 = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound1"));
	FireSound2 = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound2"));
	MagComponent = CreateDefaultSubobject<UComponent_Mag>(TEXT("MagComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent_Gunner>(TEXT("StateComponent"));
	//	AiConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIConfigSight"));
	//WeaponMesh->SetupAttachment(GetMesh(), TEXT("GunPos"));
	
	//	FireSound1->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//  FireSound2->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
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

	//	FireSound1->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//	FireSound2->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		FireSound1->SetupAttachment(WeaponMesh);
		FireSound2->SetupAttachment(WeaponMesh);
		//WeaponMesh->AttachTo(GetMesh(), TEXT("GunPos"));
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance_Gunner>ANIM(TEXT("AnimBlueprint'/Game/MyFolder/AnimationBlueprint/Anim_Gunner.Anim_Gunner_C'"));
	if (ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue>SFX_Gun1(TEXT("SoundCue'/Game/MyFolder/BP_Enemy/Gunner/SFX/AK47Que.AK47Que'"));
	if (SFX_Gun1.Succeeded())
	{
		FireSound1->Sound = SFX_Gun1.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundCue>SFX_Gun2(TEXT("SoundCue'/Game/MyFolder/BP_Enemy/Gunner/SFX/AK47Que.AK47Que'"));
	if (SFX_Gun2.Succeeded())
	{
		FireSound2->Sound = SFX_Gun2.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundAttenuation>SA_Gun(TEXT("SoundAttenuation'/Game/MyFolder/BP_Enemy/Gunner/SFX/Ak47Attenuation.Ak47Attenuation'"));
	if (SA_Gun.Succeeded())
	{
		FireSound1->AttenuationSettings = SA_Gun.Object;
		FireSound2->AttenuationSettings = SA_Gun.Object;
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

	Anim = Cast<UAnimInstance_Gunner>(GetMesh()->GetAnimInstance());
	if (!Anim)EGLOG(Error, TEXT("********Anim Cast Failed********"));

	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Gameinstance is nullptr"));
		return;
	}
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AEnemyCharacter_Gunner::LoadGame);
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AEnemyCharacter_Gunner::SaveGame);

	OnHpChangedDelegate.AddLambda([this]()->void{
		HPBar = Cast<UProgressBar>(HPBarWidget->GetUserWidgetObject()->GetWidgetFromName(TEXT("HPBar")));
		if (!HPBar)
		{
			EGLOG(Warning, TEXT(" HPBar Failed"));
			return;
		}
		HPBar->SetPercent(StateComponent->GetHPRatio());
	});

	OnHPIsZeroDelegate.AddLambda([this]()->void {
		//Anim Dead 설정
		//AIController 중단

		Anim->SetDead(true);
		auto AICon = Cast<AEnemyAIController_Gunner>(GetController());
		if (AICon)
		{
			AICon->StopAI();
		}


	});
	


//	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this,&AEnemyCharacter_Gunner::perceptionUpdated);

}

void AEnemyCharacter_Gunner::BeginPlay()
{
	Super::BeginPlay();
	//if(WeaponMesh)
	WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GunPos"));
	//EGLOG(Error, TEXT("Chara Begin"));
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
	StateComponent->SaveGame(*SaveData);
	

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
	StateComponent->LoadGame(*LoadData);
}

void  AEnemyCharacter_Gunner::initComponents()
{
	

	loadAssets();
}

void  AEnemyCharacter_Gunner::loadAssets()
{
	
}

void AEnemyCharacter_Gunner::playGunSFX()
{
	bool bTemp = UKismetMathLibrary::RandomBool();

	if (bTemp)
		FireSound1->Play();
	else
		FireSound2->Play();
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
	Anim->PlayFire(StateComponent->GetState());
	playGunSFX();
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
	Anim->PlayReload(StateComponent->GetState());


}
void AEnemyCharacter_Gunner::SetADS()
{
	StateComponent->SetState(EGunnerState::E_ADS);
	Anim->SetIronsights(true);

}
void AEnemyCharacter_Gunner::ReleaseADS()
{
	StateComponent->SetState(EGunnerState::E_Idle);
	Anim->SetIronsights(false);
}

float AEnemyCharacter_Gunner::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	StateComponent->TakeDamage(FinalDamage);

	//죽었다면 causer가 player인지 검사하고 경험치를 준다
	if (StateComponent->GetHPRatio() <= 0.0f)
	{
		auto player = Cast<AEGPlayerCharacter>(DamageCauser);
		if (player)
		{
			player->GetStatComponent()->GainExp(StateComponent->GetExp());
		}
	}


	return FinalDamage;
}

