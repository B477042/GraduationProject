// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Anim_Weapon.h"
#include "GameFramework/Character.h"
// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MainBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MAINBODY"));
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	
	RootComponent = SceneRoot;
	MainBody->AttachTo(RootComponent);
	MainBody->SetRelativeRotation(FRotator(0,-90,0));
	

	WeaponType = EWeaponTypes::Default;
	//OwnerCharacter = nullptr;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	


}
void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	Anim = Cast<UAnim_Weapon>(MainBody->GetAnimInstance());
	if (!Anim)
	{
		EGLOG(Log, TEXT("Casting Error"));
		return;
	}


	 
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::AttachedBy(ACharacter* OtherCharacter)
{
	if (GetOwner())
	{
		EGLOG(Error, TEXT("Owner Character is already setted"));
		return;
	}
	//setown = OtherCharacter;
}



 

 

 