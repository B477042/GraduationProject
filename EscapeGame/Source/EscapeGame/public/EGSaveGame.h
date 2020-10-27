// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Engine/DataTable.h"
#include "EGSaveGame.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FGameProgressData
{
	GENERATED_BODY()
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")


};

 //기본적인 좌표계를 저장하는 
USTRUCT(BlueprintType)
struct FBasicData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString ActorName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FRotator Rotation;
	
};

USTRUCT(BlueprintType)
struct FPlayerData :public FBasicData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 n_CardKeys;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 n_RecoveryItmes;


};

USTRUCT(BlueprintType)
struct FEnemyData :public FBasicData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Type;

};




UCLASS()
class ESCAPEGAME_API UEGSaveGame : public USaveGame
{
	GENERATED_BODY()
	
};
