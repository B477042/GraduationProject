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
	MainBody->AttachTo(RootComponent);
	MainBody->SetRelativeRotation(FRotator(0,-90,0));
	

	WeaponType = EWeaponTypes::Default;
	FireControl_DistanceOffset = 30.0f;
	FireControl_Radius = 200.0f;

	MainBody->SetCollisionProfileName(TEXT("NoCollision"));
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

	FVector DistVec = TargetLocation - MuzzleLocation;
	//DistVec.Normalize();
	//원의 중심 위치
	//FVector Center =  MuzzleLocation + (TargetLocation * FireControl_DistanceOffset);
	FVector Center = DistVec* FireControl_DistanceOffset;
	//조준 지점. 원의 위치에서 랜덤하게 한다
	FVector AimPoint;
	AimPoint.X = FMath::RandRange(Center.X - FireControl_Radius, Center.X + FireControl_Radius);
	AimPoint.Y = FMath::RandRange(Center.Y - FireControl_Radius, Center.Y + FireControl_Radius);
	AimPoint.Z = FMath::RandRange(Center.Z - FireControl_Radius, Center.Z + FireControl_Radius);

	//
	


	 AimPoint.Normalize();
	 //EGLOG(Log, TEXT("Anim Point is normalized : %s"), *AimPoint.ToString());
	 //EGLOG(Log, TEXT("TargetLocation is : %s"), *TargetLocation.ToString());

	 Retval = AimPoint;


	return Retval;
}

FRotator AWeapon::CalcRotationForBullet(const FVector& FireDirection)
{
	FRotator Retval = GetActorRotation();
	FVector FW = GetActorForwardVector();
	
	EGLOG(Log, TEXT("Forward : %s"), *FW.ToString());
	EGLOG(Log, TEXT("Fire Direction : %s"), *FireDirection.ToString());


	float Dot = FVector::DotProduct(FW, FireDirection);
	float Angle = FMath::Acos(Dot / (FW.Size() * FireDirection.Size()))*100;
	EGLOG(Warning, TEXT("Angle : %f"), Angle);
	Retval.Yaw += Angle;
	
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
	if (bIsEjcting)
	{
		return false;
	}

	FVector FireLocation = MainBody->GetSocketLocation(Name_Muzzle);
	
	FVector FireDirection = CalcFireDirection(TargetLocation); 
	
	FRotator FireRotation = CalcRotationForBullet(FireDirection);


	Mag->FireBullet(FireLocation, FireRotation, FireDirection);
	bIsEjcting = true;
	Anim->SetIsFired(true);
	//SetActorTickEnabled(true);

	return true;
}





 

 

 