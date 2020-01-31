// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance_Player.h"


UCharacterAnimInstance_Player::UCharacterAnimInstance_Player()
{

	static ConstructorHelpers::FObjectFinder <UAnimMontage>NORMAL_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_NormalAttack.m_NormalAttack'"));
	if (NORMAL_ATTACK.Succeeded())
	{
		AttackMontage = NORMAL_ATTACK.Object;
		//EGLOG(Error, TEXT("Montage vailed"));
	}

	static ConstructorHelpers::FObjectFinder <UAnimMontage>AIR_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_AirAttackMontage.m_AirAttackMontage'"));
	if (AIR_ATTACK.Succeeded())
	{
		AirAttackMontage = AIR_ATTACK.Object;
	}
}

void UCharacterAnimInstance_Player::JumpToComboAttackSection(int32 NewSection)
{
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
}

void UCharacterAnimInstance_Player::JumpToChargetAttackSection(int32 NewSection)
{
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
}
