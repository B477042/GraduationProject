// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnimInstance.h"
#include "..\public\CharacterAnimInstance.h"


UCharacterAnimInstance::UCharacterAnimInstance()
{
	CurrentCharacterSpeed = 0.0f;
	PriviousCharacterHeight = 0.0f;
	HeightVariation = 0.0f;
	IsInAir = false;

	StartCombo = 0;
	EndCombo = 0;
	//
	
}


void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentCharacterSpeed = Pawn->GetVelocity().Size();
		HeightVariation = Pawn->GetActorLocation().Z - PriviousCharacterHeight;
		PriviousCharacterHeight = Pawn->GetActorLocation().Z;
		

		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetCharacterMovement()->IsFalling();

		/*	if (Character->GetCharacterMovement()->GetCurrentAcceleration() != FVector::ZeroVector)
				IsAccelerating=true;
			else IsAccelerating = false;*/
		}

	}
	//EGLOG(Warning, TEXT("Tick"));
}

void UCharacterAnimInstance::BPBeginPlay()
{
	//EGLOG(Warning, TEXT("Anim Blueprint Begin!!!"));
	//EGLOG(Warning, TEXT("Anim Bp Owner name : %s"), *GetOwningActor()->GetName());
	/*Character = Cast<AEGPlayerCharacter>(GetOwningActor());
	if (Character != nullptr)
		EGLOG(Warning, TEXT("Character Name : %s"), *Character->GetName());
*/
	
}

void UCharacterAnimInstance::PlayAttackMontage()
{
	
		Montage_Play(AttackMontage, 1.0f);


}

//void UCharacterAnimInstance::PlayAirAttackMontage()
//{
//	Montage_Play(AirAttackMontage,1.0f);
//}

//void UCharacterAnimInstance::JumpToComboAttackSection(int32 NewSection)
//{
//	
//
//}
//
//void UCharacterAnimInstance::JumpToChargetAttackSection(int32 NewSection)
//{
//
//	
//}

//공격 애니메이션 재생되고 다음 애니메이션을 재생할지 검사하는 타이밍에 나온다
void UCharacterAnimInstance::AnimNotify_CanComboAttack()
{
	//EGLOG(Warning, TEXT("AnimNotify_CanCombo"));
	OnComboAttackCheckDelegate.Broadcast();
}

//공격 애니메이션 재생되고 다음 애니메이션을 재생할지 검사하는 타이밍에 나온다
void UCharacterAnimInstance::AnimNotify_CanChargeAttack()
{
	//EGLOG(Warning, TEXT("AnimNotify_CanCharge"));
	OnChargeAttackCheckDelegate.Broadcast();
	//Called Function in EGPlayerCharaceter;
	
}


FName UCharacterAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	//if(StartCombo<=0||EndCombo<=StartCombo)
	if (!FMath::IsWithinInclusive<int32>(Section, StartCombo, EndCombo))return FName(*FString::Printf(TEXT("Failed")));
	return FName(*FString::Printf(TEXT("ComboAttack%d"), Section));
}

