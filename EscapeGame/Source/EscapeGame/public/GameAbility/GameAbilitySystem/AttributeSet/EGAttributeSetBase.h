// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "EGAttributeSetBase.generated.h"

/**
 * 
 */
// Attribute.h 408 line
// getter setter property 얻는 함수 메크로
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/*
 * Base는 상호작용 가능한 오브젝트들을
 */
UCLASS(Blueprintable)
class ESCAPEGAME_API UEGAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;


	// Data Property
public:
	UPROPERTY(BlueprintReadOnly, Category = "Status", ReplicatedUsing = OnRep_HealthPoint)
	FGameplayAttributeData HealthPoint;
	ATTRIBUTE_ACCESSORS(UEGAttributeSetBase, HealthPoint)

	UPROPERTY(BlueprintReadOnly, Category = "Status", ReplicatedUsing = OnRep_MaxHealthPoint)
	FGameplayAttributeData MaxHealthPoint;
	ATTRIBUTE_ACCESSORS(UEGAttributeSetBase, MaxHealthPoint)


protected:
	UFUNCTION()
	virtual void OnRep_HealthPoint(const FGameplayAttributeData& OldHealthPoint);
	UFUNCTION()
	virtual void OnRep_MaxHealthPoint(const FGameplayAttributeData& OldMaxHealthPoint);

	virtual void ClampAttributeForMaxChange(FGameplayAttributeData& AffectedAttributeData, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
