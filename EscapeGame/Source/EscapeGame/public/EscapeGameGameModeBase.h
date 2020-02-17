// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/GameModeBase.h"

#include "EscapeGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AEscapeGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		AEscapeGameGameModeBase();
public:
	virtual void PostLogin(APlayerController* NewPlayer)override;


};
