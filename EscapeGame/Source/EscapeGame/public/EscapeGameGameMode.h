// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/GameMode.h"
#include "EscapeGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AEscapeGameGameMode : public AGameMode
{
	GENERATED_BODY()
		AEscapeGameGameMode();
public:
	virtual void PostLogin(APlayerController* NewPlayer)override;

	virtual void PostInitializeComponents() override;

	//UPROPERTY()
	//class AEGGameState* EGGameState;

};
