// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter_Gunner.h"
#include "EnemyGunnerAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimInstance_Gunner.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyCharacter_Gunner::AEnemyCharacter_Gunner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyGunnerAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	initComponents();

	bCanFire = true;
	Cooltime = 0.0f;

	Point_Muzzle = FVector::ZeroVector;

	setupPerception();
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

		EGLOG(Warning, TEXT("Can fire"));	
	//tick 중단
		SetActorTickEnabled(false);
	}


}


void AEnemyCharacter_Gunner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Anim = Cast<UAnimInstance_Gunner>(GetMesh()->GetAnimInstance());
	if (!Anim)EGLOG(Error, TEXT("********Anim Cast Failed********"));


	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this,&AEnemyCharacter_Gunner::perceptionUpdated);

}

void AEnemyCharacter_Gunner::BeginPlay()
{
	Super::BeginPlay();


}

void AEnemyCharacter_Gunner::BeginDestroy()
{
	Super::BeginDestroy();

}



void AEnemyCharacter_Gunner::SaveGame(UEGSaveGame * SaveInstance)
{
	//Super::SaveGame(SaveInstance);
}

void AEnemyCharacter_Gunner::LoadGame(const UEGSaveGame * LoadInstance)
{
	//Super::LoadGame(LoadInstance);

}
void AEnemyCharacter_Gunner::perceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	Super::perceptionUpdated(UpdatedActors);


}
void  AEnemyCharacter_Gunner::initComponents()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	FireSound1 = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound1"));
	FireSound2 = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound2"));
	MagComponent = CreateDefaultSubobject<UComponent_Mag>(TEXT("MagComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent_Gunner>(TEXT("StateComponent"));
	AiConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIConfigSight"));

	WeaponMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//	FireSound1->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//  FireSound2->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	

	loadAssets();
}

void  AEnemyCharacter_Gunner::loadAssets()
{
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
		WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,TEXT("GunPos"));
	

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

}

void AEnemyCharacter_Gunner::playGunSFX()
{
	bool bTemp = UKismetMathLibrary::RandomBool();

	if (bTemp)
		FireSound1->Play();
	else
		FireSound2->Play();
}

void AEnemyCharacter_Gunner::setupPerception()
{
	//UAISenseConfig AISenseConfig;
//	FAISenseID
	//AIPerceptionComponent->ConfigureSense

	//https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAISenseConfig_Sight/index.html
	//UAISenseConfig_Sight Document
	//UAISenseConfig_Sight senseConfig_Sight;
	AiConfigSight->SightRadius = 1500.0f;
	AiConfigSight->LoseSightRadius = 3100.0f;
	AiConfigSight->PeripheralVisionAngleDegrees = 90.0f;
	AiConfigSight->DetectionByAffiliation.bDetectEnemies = false;
	AiConfigSight->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*AiConfigSight);
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());

	


}

void AEnemyCharacter_Gunner::Attack()
{

	if (!bCanFire)
	{
		EGLOG(Error, TEXT("Cant fire"));
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

