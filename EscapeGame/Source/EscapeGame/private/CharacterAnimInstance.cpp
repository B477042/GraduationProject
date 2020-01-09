// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnimInstance.h"
#include "..\public\CharacterAnimInstance.h"


UCharacterAnimInstance::UCharacterAnimInstance()
{
	CurrentCharacterSpeed = 0.0f;
	PriviousCharacterHight = 0.0f;
	HightVariation = 0.0f;
	IsInAir = false;

	//
	static ConstructorHelpers::FObjectFinder <UAnimMontage>NORMAL_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_NormalAttack.m_NormalAttack'"));
	if (NORMAL_ATTACK.Succeeded())
	{
		AttackMontage = NORMAL_ATTACK.Object;
		//EGLOG(Error, TEXT("Montage vailed"));
	}
}


void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentCharacterSpeed = Pawn->GetVelocity().Size();
		HightVariation = Pawn->GetActorLocation().Z - PriviousCharacterHight;
		PriviousCharacterHight = Pawn->GetActorLocation().Z;
		

		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetCharacterMovement()->IsFalling();

		/*	if (Character->GetCharacterMovement()->GetCurrentAcceleration() != FVector::ZeroVector)
				IsAccelerating=true;
			else IsAccelerating = false;*/
		}

	}
}

void UCharacterAnimInstance::BPBeginPlay()
{
	EGLOG(Warning, TEXT("Anim Blueprint Begin!!!"));
	//EGLOG(Warning, TEXT("Anim Bp Owner name : %s"), *GetOwningActor()->GetName());
	/*Character = Cast<AEGPlayerCharacter>(GetOwningActor());
	if (Character != nullptr)
		EGLOG(Warning, TEXT("Character Name : %s"), *Character->GetName());
*/
	
}

void UCharacterAnimInstance::PlayNormalAttackMontage()
{
	/*EGLOG(Warning, TEXT("Mon enter"));
	if (!Montage_IsPlaying(NormalAttackMontage))
	{*/
		Montage_Play(AttackMontage, 1.0f);
	/*	EGLOG(Warning, TEXT("Mon ATtack"));
	}*/

}

void UCharacterAnimInstance::JumpToComboAttackSection(int32 NewSection)
{
	if(!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
	Montage_JumpToSection(GetComboMontageSectionName(NewSection));

}

void UCharacterAnimInstance::JumpToChargetAttackSection(int32 NewSection)
{
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
	EGLOG(Warning, TEXT("Not impelemented"));
}

void UCharacterAnimInstance::AnimNotify_CanNextAttack()
{
	OnComboAttackCheckDelegate.Broadcast();
}

void UCharacterAnimInstance::AnimNotify_CanChargeAttack()
{
	OnChargeAttackCheckDelegate.Broadcast();
	//Called Function in EGPlayerCharaceter;
}

FName UCharacterAnimInstance::GetComboMontageSectionName(int32 Section)
{
	if (!FMath::IsWithinInclusive<int32>(Section, 1, 4))return;
	return FName(*FString::Printf(TEXT("ComboAttack%d"),Section));
}

