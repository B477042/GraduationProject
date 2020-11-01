// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/PlayerState.h"
#include "EGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AEGPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AEGPlayerState();


	UFUNCTION(BlueprintCallable)
		void SaveGame();
	UFUNCTION(BlueprintCallable)
		void LoadGame();

	FString SaveSlotName;

	

};
