// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Player.h"
#include "..\public\Anim_Player.h"


UAnim_Player::UAnim_Player()
{

	static ConstructorHelpers::FObjectFinder <UAnimMontage>NORMAL_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_NormalAttack.m_NormalAttack'"));
	if (NORMAL_ATTACK.Succeeded())
	{
		AttackMontage = NORMAL_ATTACK.Object;
		EGLOG(Error, TEXT("Montage vailed"));
	}
	else
	{
		EGLOG(Warning, TEXT(" Attack montage is null"));
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
	if (AttackMontage == nullptr)EGLOG(Warning, TEXT("Attack mon is null"));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
}

void UAnim_Player::JumpToChargetAttackSection(int32 NewSection)
{
	if (AttackMontage == nullptr)EGLOG(Warning, TEXT("Mon is null"));
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
}

FName UAnim_Player::GetAttackMontageSectionName(int32 Section)
{
	if (AttackMontage == nullptr)EGLOG(Warning, TEXT("Mon is null"));

	if (!FMath::IsWithinInclusive<int32>(Section, StartCombo, EndCombo))return FName(*FString::Printf(TEXT("Failed")));
	return FName(*FString::Printf(TEXT("ComboAttack%d"), Section));

}

void UAnim_Player::PlayAttackMontage()
{
	//EGLOG(Warning, TEXT("Anim_Play montage"));
	//Super::PlayAttackMontage();

	EGLOG(Warning, TEXT("Mon enter"));
	/*if (!Montage_IsPlaying(NormalAttackMontage))
	{*/
	if (AttackMontage == nullptr)EGLOG(Warning, TEXT("Attack mon is null"));

	Montage_Play(AttackMontage, 1.0f);
	/*	EGLOG(Warning, TEXT("Mon ATtack"));
	}*/
}

void UAnim_Player::PlayAirAttackMontage()
{
	Montage_Play(AirAttackMontage, 1.0f);

}

UAnimMontage * UAnim_Player::GetAttackMontage() const
{
	return AttackMontage;
}
