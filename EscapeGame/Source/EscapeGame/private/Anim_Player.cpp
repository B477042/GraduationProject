// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Player.h"


UAnim_Player::UAnim_Player()
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
	StartCombo = 1;//Attack Montage에서 처음 액션 번호
	EndCombo = 4;//Attack Montage에서 마지막 액션 번호
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
