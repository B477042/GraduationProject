// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Engine/DataTable.h"
#include "EGSaveGame.generated.h"

/**
 * 
 */

//������ ���� ��Ȳ�� ���� ������ ����
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

 //�⺻���� ��ǥ�踦 ����
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
//Player�� �����͸� ����
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
//Enemy�� ����ϴ� Ŭ�������� ���� ����
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
//Boss�� ������ �����մϴ�
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
	//False��� ���������� �ʴ´�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool bIsVaild;


};

//PostProcess ����Ʈ ���� ���� ����
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
	//���� �����Ϳ� ������ �̸����� ������ �����մϴ�
	UPROPERTY( BlueprintReadWrite, Category = "Data")
		TMap<FString, FEnemyData> D_Enemies;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
		FBossData BossData;
	//���� �����Ϳ� ������ �̸����� ������ �����մϴ�
	UPROPERTY( BlueprintReadWrite, Category = "Data")
		TMap<FString, FItemData> D_Items;
	UPROPERTY(BlueprintReadWrite, Category = "Data")
		FGameProgressData GameProgressData;
	UPROPERTY(BlueprintReadWrite, Category = "Data")
		FPostProcessData PostProcessData;
	
};
