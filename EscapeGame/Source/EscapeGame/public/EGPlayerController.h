// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/PlayerController.h"
#include "EGPlayerController.generated.h"

/**
 * 
 */


UCLASS()
class ESCAPEGAME_API AEGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AEGPlayerController();
	virtual void PostInitializeComponents()override;
	virtual void Possess(APawn* aPawn)override;
public:
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* HUD;
};
