// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "EscapeGame.h"
#include "GameFramework/PlayerState.h"
#include "EGPlayerState.generated.h"

class AEGPlayerController;
class UEGCharacterAttributeSet;
class UAbilitySystemComponent;


#define ATTRIBUTE_VALUE_GETTER(PropertyName) \
	public:\
	UFUNCTION(BlueprintCallable, Category="Attributes") \
	float Get##PropertyName() const; \
	protected:\
	FDelegateHandle On##PropertyName##ChanegedDelegateHandle;\
	virtual void On##PropertyName##Changed(const FOnAttributeChangeData& Data);


/**
 * 
 */
UCLASS(Blueprintable)
class ESCAPEGAME_API AEGPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AEGPlayerState();

	virtual void BeginPlay() override;
	
	UEGCharacterAttributeSet* GetAttributeSet() const {return PlayerAttributeSet;}
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent;}

//* Attributes Getter
	ATTRIBUTE_VALUE_GETTER(AttackPoint)
	ATTRIBUTE_VALUE_GETTER(Level)
	ATTRIBUTE_VALUE_GETTER(ExpPoint)
	ATTRIBUTE_VALUE_GETTER(ExpBounty)
	ATTRIBUTE_VALUE_GETTER(ManaPoint)
	ATTRIBUTE_VALUE_GETTER(MaxManaPoint)
	ATTRIBUTE_VALUE_GETTER(StaminaPoint)
	ATTRIBUTE_VALUE_GETTER(MaxStaminaPoint)
	
protected:
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	TObjectPtr<AEGPlayerController> getEGPlayerController();

	
	
protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UEGCharacterAttributeSet* PlayerAttributeSet;

};
