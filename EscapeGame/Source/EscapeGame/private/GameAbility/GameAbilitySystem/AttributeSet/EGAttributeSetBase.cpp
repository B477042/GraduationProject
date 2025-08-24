// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/GameAbilitySystem/AttributeSet/EGAttributeSetBase.h"

#include "Net/UnrealNetwork.h"

void UEGAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UEGAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UEGAttributeSetBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UEGAttributeSetBase,HealthPoint,COND_None,REPNOTIFY_Always)
}

void UEGAttributeSetBase::OnRep_HealthPoint(const FGameplayAttributeData& OldHealthPoint)
{
}

void UEGAttributeSetBase::OnRep_MaxHealthPoint(const FGameplayAttributeData& OldMaxHealthPoint)
{
}

void UEGAttributeSetBase::ClampAttributeForMaxChange(FGameplayAttributeData& AffectedAttributeData,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	
	if (TObjectPtr<UAbilitySystemComponent> abilitySystemComponent = GetOwningAbilitySystemComponent())
	{
		const float maxValue = MaxAttribute.GetCurrentValue();
		
	}
}
