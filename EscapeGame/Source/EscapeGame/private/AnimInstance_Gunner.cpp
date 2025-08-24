// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstance_Gunner.h"

#include "KismetAnimationLibrary.h"
#include "KismetAnimationLibrary.h"
#include "KismetAnimationLibrary.h"
#include "Actor/Character/EnemyCharacter_Gunner.h"
#include "Component/StatComponent_Gunner.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"



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
	bIsDead = false;
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
	static ConstructorHelpers::FObjectFinder<USoundWave>SW_Dead(TEXT("SoundWave'/Game/MyFolder/Sound/Voice/396801__scorpion67890__male-death-4.396801__scorpion67890__male-death-4'"));
	if (SW_Dead.Succeeded())
	{
		SFX_Dead = SW_Dead.Object;
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
	
	//Update Direction bs_Walk
	Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
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
void UAnimInstance_Gunner::SetDead(bool bSet)
{
	bIsDead = bSet;
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

void UAnimInstance_Gunner::AnimNotify_Anim_DeadStart()
{
	StopAllMontages(0);
	UGameplayStatics::PlaySoundAtLocation(this, SFX_Dead, GetOwningActor()->GetActorLocation());
	
}


void UAnimInstance_Gunner::AnimNotify_Anim_DeadEnd()
{
	Character->Dead();
}

void UAnimInstance_Gunner::AnimNotify_LeftStep()
{
	Character->PlaySFXFoot(false);
}

void UAnimInstance_Gunner::AnimNotify_RightStep()
{
	Character->PlaySFXFoot(true);
}
