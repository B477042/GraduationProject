// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Engine/DataTable.h"
#include "EGSaveGame.generated.h"

/**
 * 
 */

 //Data table to use when storing game data
USTRUCT(BlueprintType)
struct FGameDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:

};


UCLASS()
class ESCAPEGAME_API UEGSaveGame : public USaveGame
{
	GENERATED_BODY()
	
};
