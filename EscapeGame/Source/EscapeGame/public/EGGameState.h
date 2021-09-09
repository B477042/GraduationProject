// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EnemyCharacter.h"
#include "GameFramework/GameState.h"
#include "EGGameState.generated.h"

/**
 *
 */




UCLASS(Config = "GameStateValue")
class ESCAPEGAME_API AEGGameState : public AGameState
{
	GENERATED_BODY()
public:
	AEGGameState();

public:
	//Escape restriction time
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		float RemainTimes;
	

	////Level�� �����ϴ� EnemyCharacter�� ����Ʈ
	//UPROPERTY(Transient, VisibleAnywhere, Category = "List", meta = (AllowPrivateAccess = "true"))
	//	TArray<TWeakObjectPtr<AEnemyCharacter>>A_Enemies;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString LevelName;

	
};
