// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EnemyCharacter.h"
#include "GameFramework/GameState.h"
#include "EGGameState.generated.h"

/**
 *
 */
UCLASS()
class ESCAPEGAME_API AEGGameState : public AGameState
{
	GENERATED_BODY()
public:
	AEGGameState();




	//만약 loadgame으로 게임이 시작하게 된거인지면 체크한다.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		bool bIsLoadedGame;
	//Escape restriction time
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		float RemainTimes;


	//Level에 존재하는 EnemyCharacter의 리스트
	UPROPERTY(VisibleAnywhere, Category = "List", meta = (AllowPrivateAccess = "true"))
		TArray<TWeakObjectPtr<AEnemyCharacter>>A_Enemies;

	
};
