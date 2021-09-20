// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Anim_Weapon.h"
#include "GameFramework/Character.h"
#include "Component_Mag.h"
// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MainBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MAINBODY"));
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	Mag = CreateDefaultSubobject<UComponent_Mag>(TEXT("Mag"));


	RootComponent = SceneRoot;
	MainBody->AttachTo(RootComponent);
	MainBody->SetRelativeRotation(FRotator(0,-90,0));
	

	WeaponType = EWeaponTypes::Default;
 

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	//Initialize Mag Component


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

//Using Spread Sphere
FVector AWeapon::CalcFireDirection(const FVector& TargetLocation)
{
	FVector Retval = GetActorForwardVector();


	return Retval;
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


}

bool AWeapon::Attack(const FVector& TargetLocation)
{
	if (!bIsEjcting)
	{
		return false;
	}

	FVector FireLocation = MainBody->GetSocketLocation(Name_Muzzle);
	FRotator FireRotation = GetActorRotation();
	FVector FireDirection = CalcFireDirection(TargetLocation);

	Mag->FireBullet(FireLocation, FireRotation, FireDirection);
	bIsEjcting = true;

	return true;
}





 

 

 