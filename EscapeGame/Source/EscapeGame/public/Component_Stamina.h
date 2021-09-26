// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameComponent.h"
#include "Component_Stamina.generated.h"

/**
 * Deal with Stamina System
 */

//Input Param is percent of stamina
DECLARE_DELEGATE_OneParam(FOnStaminaChanged, float);




UCLASS(ClassGroup = "Custom", Config = "GameComponent", meta = (BlueprintSpawnableComponent))
class ESCAPEGAME_API UComponent_Stamina : public UGameComponent
{
	GENERATED_BODY()
public:
	UComponent_Stamina();

	//bool CanUseStamina() { return bCanUsingStamina; }
	float GetStaminaRatio();

	//
	void TurnOnStamina ();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy()override;
	
	void UsingTick(float DeltaTime);
	void RecoverTick(float DeltaTime);
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnStaminaChanged OnStaminaChanged;
protected:
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		float Stamina;
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		float MaxStamina;
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		float RecoverElement;
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		float UsingElement;


	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		uint8 bCanUsingStamina : 1;
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		uint8 bIsStaminaUsing:1;
};
