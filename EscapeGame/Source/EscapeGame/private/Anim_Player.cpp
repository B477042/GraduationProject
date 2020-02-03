// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Player.h"
#include "..\public\Anim_Player.h"


UAnim_Player::UAnim_Player()
{

	static ConstructorHelpers::FObjectFinder <UAnimMontage>NORMAL_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_NormalAttack.m_NormalAttack'"));
	if (NORMAL_ATTACK.Succeeded())
	{
		AttackMontage = NORMAL_ATTACK.Object;
	
	}
	

	static ConstructorHelpers::FObjectFinder <UAnimMontage>AIR_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_AirAttackMontage.m_AirAttackMontage'"));
	if (AIR_ATTACK.Succeeded())
	{
		AirAttackMontage = AIR_ATTACK.Object;
	}

	
	
	//UCharacterAnimInstance::StartCombo = 1;
	StartCombo = 1;
	EndCombo = 4;
}

void UAnim_Player::JumpToComboAttackSection(int32 NewSection)
{
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
	
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
}

void UAnim_Player::JumpToChargetAttackSection(int32 NewSection)
{
	
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
}

//FName UAnim_Player::GetAttackMontageSectionName(int32 Section)
//{
//	
//
//	if (!FMath::IsWithinInclusive<int32>(Section, StartCombo, EndCombo))return FName(*FString::Printf(TEXT("Failed")));
//	return FName(*FString::Printf(TEXT("ComboAttack%d"), Section));
//
//}

//void UAnim_Player::PlayAttackMontage()
//{
//	//EGLOG(Warning, TEXT("Anim_Play montage"));
//	//Super::PlayAttackMontage();
//
//	;
//	/*if (!Montage_IsPlaying(NormalAttackMontage))
//	{*/
//
//
//	Montage_Play(AttackMontage, 1.0f);
//	/*	EGLOG(Warning, TEXT("Mon ATtack"));
//	}*/
//}

void UAnim_Player::PlayAirAttackMontage()
{
	Montage_Play(AirAttackMontage, 1.0f);

}

UAnimMontage * UAnim_Player::GetAttackMontage() const
{
	return AttackMontage;
}
