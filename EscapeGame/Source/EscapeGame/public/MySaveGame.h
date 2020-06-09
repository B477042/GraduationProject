// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */

//Game Loading 방식. Load Game 인지 Next Stage인지
UENUM(BlueprintType)
enum class ELoadType : uint8 {
	LoadGame, NextStage, NewGame
};

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BasicData")
	ELoadType LoadType;



	////================================================================================
	////적의 정보
	////살아 있던 에너미들의 이름
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyData")
	//	TArray<FName> AliveEnemyName;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BossData")
	//	int Boss_Mp;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BossData")
	//	int Boss_Hp;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BossData")
	//	FVector Boss_Location;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BossData")
	//	FRotator Boss_Rotation;
	


	UMySaveGame();
	UFUNCTION(BlueprintCallable)
	void ResetData();
};
