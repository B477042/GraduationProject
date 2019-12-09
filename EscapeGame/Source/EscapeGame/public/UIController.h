// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/PlayerController.h"
#include "UIController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AUIController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay()override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = UI)
		TSubclassOf<class UUserWidget>UserWidgetClass;
	UPROPERTY()
		class UUserWidget* UIWidgetInstance;
};
