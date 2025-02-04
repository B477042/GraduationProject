// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameComponent.h"
#include "Component_Stamina.generated.h"

/**
 * Deal with Stamina System
 */


DECLARE_DELEGATE(FOnStaminaChanged);

UCLASS(ClassGroup = "Custom", Config = "GameComponent", meta = (BlueprintSpawnableComponent))
class ESCAPEGAME_API UComponent_Stamina : public UGameComponent
{
	GENERATED_BODY()
public:
	UComponent_Stamina();

	bool CanUseStamina();
	float GetStaminaRatio();

	// Tik-based stamina usage function. Like sprint, blocking
	void TurnOnTickStamina ();
	// Roll, Jump 
	bool UseStaticStamina();
	//True : Using Stamina , false : Not Using Stamina
	void SetUsingStamina(bool bResult);
	FOnStaminaChanged OnStaminaChanged;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy()override;
	
	void UsingTick();
	void RecoverTick(float DeltaTime);
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		float Stamina;
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		float MaxStamina;
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		float RecoverFactor;
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		float UsingFactor;
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		float UsageOfStatic;


	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		uint8 bCanUsingStamina : 1;
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
		uint8 bIsStaminaUsing:1;
	 
};
