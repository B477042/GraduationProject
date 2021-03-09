// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Gunner.h"
#include "Kismet/KismetMathLibrary.h"



const FName UAnimInstance_Gunner::FIRE_RIFLE_IRONSIGHTS = TEXT("Fire_Rifle_Ironsights");
const FName UAnimInstance_Gunner::FIRE_RIFLE_HIP = TEXT("Fire_Rifle_Hip");
const FName UAnimInstance_Gunner::RELOAD_RIFLE_HIP = TEXT("Reload_Rifle_Hip");
const FName UAnimInstance_Gunner::RELOAD_RIFLE_IRONSIGHTS = TEXT("Reload_Rifle_Ironsights");



UAnimInstance_Gunner::UAnimInstance_Gunner()
{
    
	bIsInAir=false;
	bIsAccelerating=false;
	bIsFullBody=false;
	bIsAttacking=false;
	bIsCrouch = false;
	bOnIronsights = false;
	Speed=0.f;
	Direction = 0.0f;

	Pitch=0.0f, Roll=0.0f, Yaw=0.0f;
	//AimPitch = 0.0f, AimYaw = 0.0f;
	YawDelta=0.0f;
	PrevPos = FVector::ZeroVector;
	RotationLastTick=FRotator::ZeroRotator;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>AM_Fire(TEXT("AnimMontage'/Game/MyFolder/BP_Enemy/Gunner/ani_source/Fire_Rifle_Ironsights_Montage.Fire_Rifle_Ironsights_Montage'"));
	if (AM_Fire.Succeeded())
	{
		FireMontage = AM_Fire.Object;
	}

	
}

void UAnimInstance_Gunner::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Character = Cast<AEnemyCharacter_Gunner>(TryGetPawnOwner());
	if (!Character)
	{
		EGLOG(Error, TEXT("CastingFailed"));
	}
}

void UAnimInstance_Gunner::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character)return;

	//update is in air
	bIsInAir = Character->GetMovementComponent()->IsFalling();

	//update speed
	Speed = Character->GetVelocity().Size();

	////update is accelerating
	//float accelerate = Character->GetCharacterMovement()->GetCurrentAcceleration().Size();
	//accelerate > 0 ? bIsAccelerating = true : bIsAccelerating = false;

	//update is fullbody
	GetCurveValue(TEXT("FullBody")) > 0 ? bIsFullBody = true : bIsFullBody = false;


	//Update pitch,yaw,roll
	RotationLastTick = Character->GetActorRotation();

	FRotator deltaRot = UKismetMathLibrary::NormalizedDeltaRotator(Character->GetBaseAimRotation(), Character->GetActorRotation());
	Pitch = deltaRot.Pitch;
	Yaw = deltaRot.Yaw;
	Roll = deltaRot.Roll;

	YawDelta = UKismetMathLibrary::FInterpTo(YawDelta, 
		UKismetMathLibrary::NormalizedDeltaRotator(RotationLastTick,Character->GetActorRotation()).Roll/DeltaSeconds/10.0f,
		DeltaSeconds,6.0f
	);

	////Update bs_Walk Speed
	//bs_Speed = UKismetMathLibrary::GetDirectionUnitVector(PrevPos,Character->GetActorLocation()).Size();
	//PrevPos = Character->GetActorLocation();
	//
	//Update Direction bs_Walk
	Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
}

void UAnimInstance_Gunner::SetCrouch(bool bSet)
{
	bIsCrouch = bSet;
}

void UAnimInstance_Gunner::SetIronsights(bool bSet)
{
	bOnIronsights = bSet;
}
void UAnimInstance_Gunner::SetAttacking(bool bSet)
{
	bIsAttacking = bSet;
}

void UAnimInstance_Gunner::SetAccelerating(bool bSet)
{
	bIsAccelerating = bSet;
}

UAnimMontage * UAnimInstance_Gunner::GetFireMontage() const
{

	return FireMontage;
}

void UAnimInstance_Gunner::PlayFire(EGunnerState State)
{
	
		if (State == EGunnerState::E_Idle)
		{
			Montage_JumpToSection(FIRE_RIFLE_HIP);
			Montage_Play(FireMontage, 1.0f);
		//	EGLOG(Warning, TEXT("idle fire"));
			return;
		}
		if (State == EGunnerState::E_ADS)
		{
			Montage_JumpToSection(FIRE_RIFLE_IRONSIGHTS);
			Montage_Play(FireMontage, 1.0f);
		//	EGLOG(Warning, TEXT("ADS fire"));
			return;
		}
	

}

void UAnimInstance_Gunner::PlayReload(EGunnerState State)
{
	
	if (State == EGunnerState::E_Idle)
	{
		Montage_JumpToSection(RELOAD_RIFLE_HIP, FireMontage);
		Montage_Play(FireMontage, 1.0f);
		return;
	}
	if (State == EGunnerState::E_ADS)
	{
		Montage_JumpToSection(RELOAD_RIFLE_IRONSIGHTS, FireMontage);
		Montage_Play(FireMontage, 1.0f);
		return;
	}
	
}
