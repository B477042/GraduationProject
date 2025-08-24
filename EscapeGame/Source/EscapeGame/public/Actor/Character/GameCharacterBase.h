// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameCharacterBase.generated.h"

class UEGCharacterAttributeSet;

class UAbilitySystemComponent;

UCLASS( Blueprintable, Abstract)
class ESCAPEGAME_API AGameCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComponent.Get();};

	void SetAbilitySystemComponent(TObjectPtr<UAbilitySystemComponent> NewAbilitySystemComponent);
	void SetAttributeSet(TObjectPtr<UEGCharacterAttributeSet> AttributeSet);	

protected:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="GameAbilitySystem",meta=(AllowPrivateAccess=true))
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="GameAbilitySystem",meta=(AllowPrivateAccess=true))
	TWeakObjectPtr<UEGCharacterAttributeSet> CharacterAttributeSet;
};
