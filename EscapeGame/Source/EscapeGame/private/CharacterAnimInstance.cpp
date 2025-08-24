// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CharacterAnimInstance.h"

#include "Actor/Character/EGPlayerCharacter.h"
#include "Component/StatComponent_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


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

//���� �ִϸ��̼� ����ǰ� ���� �ִϸ��̼��� ������� �˻��ϴ� Ÿ�ֿ̹� ���´�
void UCharacterAnimInstance::AnimNotify_CanComboAttack()
{
	//EGLOG(Warning, TEXT("AnimNotify_CanCombo"));
	//OnComboAttackCheckDelegate.Broadcast(GetCurrentActiveMontage(), false);

	auto player = Cast<AEGPlayerCharacter>(TryGetPawnOwner());
	if (player)
	{
		if (player->GetStatComponent()->CheckCanComboAttack())
		{
			EGLOG(Error, TEXT("lambda check combo"));
			//AnimNotify_CanComboAttack ���� ȣ��� �Լ���
			player->GetStatComponent()->SetComboStartState();
			JumpToComboAttackSection(player->GetStatComponent()->GetCurrentCombo());
			//Anim->Montage->Play();
		}

	}



}

//���� �ִϸ��̼� ����ǰ� ���� �ִϸ��̼��� ������� �˻��ϴ� Ÿ�ֿ̹� ���´�
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

