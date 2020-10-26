// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "DT_GameData.generated.h"

//Data table to use when storing game data
USTRUCT(BlueprintType)
struct FGameDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:

};

UCLASS()
class ESCAPEGAME_API ADT_GameData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADT_GameData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
