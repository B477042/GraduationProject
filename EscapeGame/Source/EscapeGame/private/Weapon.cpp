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
	Mag = CreateDefaultSubobject<UComponent_Mag>(TEXT("Mag"));


	RootComponent = SceneRoot;
	MainBody->SetupAttachment(RootComponent);
	MainBody->SetRelativeRotation(FRotator(0,-90,0));
	

	//WeaponType = EWeaponTypes::Default;
	FireControl_DistanceOffset = 30.0f;
	FireControl_Radius = 400.0f;

	MainBody->SetCollisionProfileName(TEXT("NoCollision"));
}

void AWeapon::BeginDestroy()
{
	Super::BeginDestroy();
	EGLOG(Log, TEXT("Weapon Destory"));
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

	//Bind Ejection
	Anim->OnEjectionEnd.BindLambda([this]()->void{
		bIsEjcting = false;
	});
	 
}

//Using Spread Sphere
FVector AWeapon::CalcFireDirection(const FVector& TargetLocation)
{
	FVector Retval = TargetLocation;

	FVector MuzzleLocation = MainBody->GetSocketLocation(Name_Muzzle);

	//Muzzle to TargetLocation
	FVector DistanceVector = TargetLocation - MuzzleLocation;
	//DistanceVector.Normalize();
	//Spread Sphere Center Location
	FVector SphereCenter = DistanceVector* FireControl_DistanceOffset;
	//조준 지점. 원의 위치에서 랜덤하게 한다
	FVector AimPoint;
	AimPoint.X = FMath::RandRange(SphereCenter.X - FireControl_Radius, SphereCenter.X + FireControl_Radius);
	AimPoint.Y = FMath::RandRange(SphereCenter.Y - FireControl_Radius, SphereCenter.Y + FireControl_Radius);
	AimPoint.Z = FMath::RandRange(SphereCenter.Z - FireControl_Radius, SphereCenter.Z + FireControl_Radius);

	AimPoint.Normalize();

	 Retval = AimPoint;


	return Retval;
}

//Reference https://amored8701.tistory.com/132
//Cross
FRotator AWeapon::CalcRotationForBullet(const FVector& FireDirection)
{
	FRotator Retval = GetActorRotation();
	FVector FW = GetActorForwardVector();
	
 
	float Dot = FVector::DotProduct(FW, FireDirection);
	float Angle = FMath::Acos(Dot / (FW.Size() * FireDirection.Size()))*100;
	EGLOG(Warning, TEXT("Angle : %f"), Angle);
	FVector Cross = FVector::CrossProduct(FW,FireDirection);
	if(Cross.Z>0)
	{
		Retval.Yaw += Angle;
		return Retval;
	}

	Retval.Yaw += -Angle;
	
	return Retval;

	
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::DiscardWeapon()
{
	Mag->ClearBullet();
	Destroy();
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
	if (bIsEjcting)
	{
		return false;
	}

	FVector FireLocation = MainBody->GetSocketLocation(Name_Muzzle);
	
	FVector FireDirection = CalcFireDirection(TargetLocation); 
	
	FRotator FireRotation = CalcRotationForBullet(FireDirection);
	//FRotator FireRotation =GetOwner()-> GetActorRotation();

	Mag->FireBullet(FireLocation, FireRotation, FireDirection);
	bIsEjcting = true;
	Anim->SetIsFired(true);
	//SetActorTickEnabled(true);

	return true;
}





 

 

 