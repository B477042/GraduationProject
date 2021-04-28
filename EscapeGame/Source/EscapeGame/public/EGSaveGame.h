// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Engine/DataTable.h"
#include "EGSaveGame.generated.h"

/**
 * 
 */

//게임의 진행 상황에 대한 정보를 저장
USTRUCT(BlueprintType)
struct FGameProgressData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float RemainTimes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float PlayerScores;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FName LevelName;

};

 //기본적인 좌표계를 저장
USTRUCT(BlueprintType)
struct FTransformData
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
//Player의 데이터를 저장
USTRUCT(BlueprintType)
struct FPlayerData :public FTransformData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 n_CardKeys;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 n_RecoverItmes;


};
//Enemy를 상속하는 클래스들의 정보 저장
USTRUCT(BlueprintType)
struct FEnemyData :public FTransformData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Type;

};
//Boss의 정보를 저장합니다
USTRUCT(BlueprintType)
struct FBossData :public FEnemyData
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool bIsMpCharging;

	FVector TargetPos;
	
	//BB Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ActionTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	uint8 BehaviorPattern;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool bIsDash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FVector BackStepPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool bSoundPlayed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MP;



};

USTRUCT(BlueprintType)
struct FItemData :public  FTransformData
{
	GENERATED_BODY()

public:
	//False라면 렌더링하지 않는다
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool bIsVaild;


};

//PostProcess 이펙트 관련 정보 저장
USTRUCT(BlueprintType)
struct FPostProcessData :public  FTransformData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector4 ColorContrastValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector4 ColorGammaValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector4 ColorSaturation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float GrainJitter ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float GrainIntensity ;

};




UCLASS()
class ESCAPEGAME_API UEGSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	//Data TArray of Players
	UPROPERTY(BlueprintReadWrite, Category = "Data")
		FPlayerData D_Player;
	//엔진 에디터에 지정된 이름으로 정보를 관리합니다
	UPROPERTY( BlueprintReadWrite, Category = "Data")
		TMap<FString, FEnemyData> D_Enemies;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
		FBossData BossData;
	//엔진 에디터에 지정된 이름으로 정보를 관리합니다
	UPROPERTY( BlueprintReadWrite, Category = "Data")
		TMap<FString, FItemData> D_Items;
	UPROPERTY(BlueprintReadWrite, Category = "Data")
		FGameProgressData GameProgressData;
	UPROPERTY(BlueprintReadWrite, Category = "Data")
		FPostProcessData PostProcessData;
	
};
