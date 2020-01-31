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
	//EGLOG(Warning, TEXT("Anim Blueprint Begin!!!"));
	//EGLOG(Warning, TEXT("Anim Bp Owner name : %s"), *GetOwningActor()->GetName());
	/*Character = Cast<AEGPlayerCharacter>(GetOwningActor());
	if (Character != nullptr)
		EGLOG(Warning, TEXT("Character Name : %s"), *Character->GetName());
*/
	
}

void UCharacterAnimInstance::PlayAttackMontage()
{
	/*EGLOG(Warning, TEXT("Mon enter"));
	if (!Montage_IsPlaying(NormalAttackMontage))
	{*/
		Montage_Play(AttackMontage, 1.0f);
	/*	EGLOG(Warning, TEXT("Mon ATtack"));
	}*/

}

void UCharacterAnimInstance::PlayAirAttackMontage()
{
	Montage_Play(AirAttackMontage,1.0f);
}

void UCharacterAnimInstance::JumpToComboAttackSection(int32 NewSection)
{
	

}

void UCharacterAnimInstance::JumpToChargetAttackSection(int32 NewSection)
{

	
}

//���� �ִϸ��̼� ����ǰ� ���� �ִϸ��̼��� ������� �˻��ϴ� Ÿ�ֿ̹� ���´�
void UCharacterAnimInstance::AnimNotify_CanComboAttack()
{
	//EGLOG(Warning, TEXT("AnimNotify_CanCombo"));
	OnComboAttackCheckDelegate.Broadcast();
}

//���� �ִϸ��̼� ����ǰ� ���� �ִϸ��̼��� ������� �˻��ϴ� Ÿ�ֿ̹� ���´�
void UCharacterAnimInstance::AnimNotify_CanChargeAttack()
{
	//EGLOG(Warning, TEXT("AnimNotify_CanCharge"));
	OnChargeAttackCheckDelegate.Broadcast();
	//Called Function in EGPlayerCharaceter;
}

//Section���� Combo���� ��ġ �ϴ��� �˻��Ѵ�
//��ġ ���� �ʴ´ٸ� Failed��� FName�� ��ȯ�ȴ�
FName UCharacterAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	if (!FMath::IsWithinInclusive<int32>(Section, StartCombo, EndCombo))return FName(*FString::Printf(TEXT("Failed")));
	return FName(*FString::Printf(TEXT("ComboAttack%d"),Section));
}

