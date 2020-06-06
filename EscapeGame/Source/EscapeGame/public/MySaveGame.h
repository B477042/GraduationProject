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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
	int Level;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
	int NextExp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
		int CurrentHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
		float RemainTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
		int n_RecoveryItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
		int n_CardKey;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
	FVector LastLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
	FRotator LastRotator;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
	int32 UserIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasicData")
		FName WorldName;


	UMySaveGame();
	UFUNCTION(BlueprintCallable)
	void ResetData();
};
