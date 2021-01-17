// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter_Gunner.h"
#include "EnemyGunnerAIController.h"

AEnemyCharacter_Gunner::AEnemyCharacter_Gunner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyGunnerAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;



}
void  AEnemyCharacter_Gunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEnemyCharacter_Gunner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

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
	Super::SaveGame(SaveInstance);
}

void AEnemyCharacter_Gunner::LoadGame(const UEGSaveGame * LoadInstance)
{
	Super::LoadGame(LoadInstance);

}
void  AEnemyCharacter_Gunner::initComponents()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	FireSound1 = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound1"));
	FireSound2 = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound2"));


	WeaponMesh->AttachTo(RootComponent);
	FireSound1->AttachTo(WeaponMesh);
	FireSound2->AttachTo(WeaponMesh);
}

void  AEnemyCharacter_Gunner::loadAssets()
{
	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;
	float X = 0.0f, Y = 0.0f, Z = 0.0f;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_BODY(TEXT("SkeletalMesh'/Game/Scanned3DPeoplePack/RP_Character/rp_nathan_rigged_003_Mobile_ue4/rp_nathan_rigged_003_Mobile_ue4.rp_nathan_rigged_003_Mobile_ue4'"));
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
		WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	}

}