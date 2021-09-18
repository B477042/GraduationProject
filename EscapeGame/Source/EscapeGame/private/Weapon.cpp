// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "EGPlayerCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MAINBODY"));
	VFX_Muzzle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX_Muzzle"));
	SFX_Muzzle = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Muzzle"));

 
	
	MainBody->SetupAttachment(RootComponent);
	SFX_Muzzle->SetupAttachment(VFX_Muzzle);

	WeaponType = EWeaponTypes::Default;
 

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
 

}
void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	 
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeapon::AttachMuzzleEffect()
{
	return VFX_Muzzle->AttachToComponent(MainBody, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Muzzle");

}
 
 

 

 