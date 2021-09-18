// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Anim_Weapon.h"
// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MAINBODY"));

	MainBody->SetupAttachment(RootComponent);
	MainBody->SetRelativeRotation(FRotator(0.0f,90.0f,0.0f));


	WeaponType = EWeaponTypes::Default;
 

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	VFX_Muzzle->AttachToComponent(MainBody, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Muzzle");

}
void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	Anim = Cast<UAnim_Weapon>(MainBody->)
	 
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



 

 

 