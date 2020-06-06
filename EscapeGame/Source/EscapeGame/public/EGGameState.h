// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
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
	
};
