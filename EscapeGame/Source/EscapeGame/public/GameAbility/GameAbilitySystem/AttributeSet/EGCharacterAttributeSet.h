// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EGAttributeSetBase.h"
#include "EGCharacterAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Character type actor
 */
UCLASS()
class ESCAPEGAME_API UEGCharacterAttributeSet : public UEGAttributeSetBase
{
	GENERATED_BODY()
public:

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


	
	UPROPERTY(BlueprintReadOnly, Category = "Status", ReplicatedUsing = OnRep_AttackPoint)
	FGameplayAttributeData AttackPoint;
	ATTRIBUTE_ACCESSORS(UEGCharacterAttributeSet, AttackPoint)

	UPROPERTY(BlueprintReadOnly, Category = "Status|Level", ReplicatedUsing = OnRep_Level);
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UEGCharacterAttributeSet, Level)

	UPROPERTY(BlueprintReadOnly, Category = "Status|Level", ReplicatedUsing = OnRep_ExpPoint);
	FGameplayAttributeData ExpPoint;
	ATTRIBUTE_ACCESSORS(UEGCharacterAttributeSet, ExpPoint)
	
	UPROPERTY(BlueprintReadOnly, Category = "Status|Level", ReplicatedUsing = OnRep_ExpBounty);
	FGameplayAttributeData ExpBounty;
	ATTRIBUTE_ACCESSORS(UEGCharacterAttributeSet, ExpBounty)
	
	
	UPROPERTY(BlueprintReadOnly, Category = "Status|Mana", ReplicatedUsing = OnRep_ManaPoint);
	FGameplayAttributeData ManaPoint;
	ATTRIBUTE_ACCESSORS(UEGCharacterAttributeSet, ManaPoint)

	UPROPERTY(BlueprintReadOnly, Category = "Status|Mana", ReplicatedUsing = OnRep_MaxManaPoint);
	FGameplayAttributeData MaxManaPoint;
	ATTRIBUTE_ACCESSORS(UEGCharacterAttributeSet, MaxManaPoint)

	UPROPERTY(BlueprintReadOnly, Category = "Status|Stamina", ReplicatedUsing = OnRep_StaminaPoint);
	FGameplayAttributeData StaminaPoint;
	ATTRIBUTE_ACCESSORS(UEGCharacterAttributeSet, StaminaPoint)

	UPROPERTY(BlueprintReadOnly, Category = "Status|Stamina", ReplicatedUsing = OnRep_MaxStaminaPoint);
	FGameplayAttributeData MaxStaminaPoint;
	ATTRIBUTE_ACCESSORS(UEGCharacterAttributeSet, MaxStaminaPoint)


protected:
	UFUNCTION()
	virtual void OnRep_AttackPoint(const FGameplayAttributeData& OldAttackPoint);
	UFUNCTION()
	virtual void OnRep_Level(const FGameplayAttributeData& OldLevel);
	UFUNCTION()
	virtual void OnRep_ManaPoint(const FGameplayAttributeData& OldManaPoint);
	UFUNCTION()
	virtual void OnRep_MaxManaPoint(const FGameplayAttributeData& OldMaxManaPoint);
	UFUNCTION()
	virtual void OnRep_StaminaPoint(const FGameplayAttributeData& OldStaminaPoint);
	UFUNCTION()
	virtual void OnRep_ExpPoint(const FGameplayAttributeData& OldExpPoint);
	UFUNCTION()
	virtual void OnRep_ExpBounty(const FGameplayAttributeData& OldExpBounty);
	UFUNCTION()
	virtual void OnRep_MaxStaminaPoint(const FGameplayAttributeData& OldMaxStaminaPoint);

};
