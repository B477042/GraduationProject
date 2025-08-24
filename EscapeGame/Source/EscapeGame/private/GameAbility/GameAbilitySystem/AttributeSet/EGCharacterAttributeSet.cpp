// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GameAbilitySystem/AttributeSet/EGCharacterAttributeSet.h"

void UEGCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Clamp가 필요한 attribute들 처리
	
}

void UEGCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UEGCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UEGCharacterAttributeSet::OnRep_AttackPoint(const FGameplayAttributeData& OldAttackPoint)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEGCharacterAttributeSet,AttackPoint,OldAttackPoint);
}

void UEGCharacterAttributeSet::OnRep_Level(const FGameplayAttributeData& OldLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEGCharacterAttributeSet,Level,OldLevel);
}

void UEGCharacterAttributeSet::OnRep_ManaPoint(const FGameplayAttributeData& OldManaPoint)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEGCharacterAttributeSet,ManaPoint,OldManaPoint);
}

void UEGCharacterAttributeSet::OnRep_MaxManaPoint(const FGameplayAttributeData& OldMaxManaPoint)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEGCharacterAttributeSet,MaxManaPoint,OldMaxManaPoint);
}

void UEGCharacterAttributeSet::OnRep_StaminaPoint(const FGameplayAttributeData& OldStaminaPoint)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEGCharacterAttributeSet,StaminaPoint,OldStaminaPoint);
}

void UEGCharacterAttributeSet::OnRep_ExpPoint(const FGameplayAttributeData& OldExpPoint)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEGCharacterAttributeSet,ExpPoint,OldExpPoint);
}

void UEGCharacterAttributeSet::OnRep_ExpBounty(const FGameplayAttributeData& OldExpBounty)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEGCharacterAttributeSet,ExpBounty,OldExpBounty);
}

void UEGCharacterAttributeSet::OnRep_MaxStaminaPoint(const FGameplayAttributeData& OldMaxStaminaPoint)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEGCharacterAttributeSet,StaminaPoint,OldMaxStaminaPoint);
}
