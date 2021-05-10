// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EnemyCharacter.h"
#include "GameFramework/GameState.h"
#include "EGGameState.generated.h"

/**
 *
 */

//UENUM(BlueprintType)
//enum class EEGGameState :uint8
//{
//	E_InPlay=0 UMETA(DisplayName = "InPlay"),
//	E_NewGame  UMETA(DisplayName = "NewGame"),
//	E_LoadGame UMETA(DisplayName = "LoadGame"),
//	E_ClearGame UMETA(DisplayName = "ClearGame"),
//	E_NextStage UMETA(DisplayName = "NextStage")
//	
//};


UCLASS()
class ESCAPEGAME_API AEGGameState : public AGameState
{
	GENERATED_BODY()
public:
	AEGGameState();

public:
	//Escape restriction time
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		float RemainTimes;
	

	//Level에 존재하는 EnemyCharacter의 리스트
	UPROPERTY(Transient, VisibleAnywhere, Category = "List", meta = (AllowPrivateAccess = "true"))
		TArray<TWeakObjectPtr<AEnemyCharacter>>A_Enemies;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString LevelName;

	
};
