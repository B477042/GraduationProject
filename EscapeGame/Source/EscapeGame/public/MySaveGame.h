// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int Level;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int NextExp;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector LastLocation;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FRotator LastRotator;


	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;


	UMySaveGame();
};
