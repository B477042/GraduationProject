// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "AIController.h"
#include "AIController_Boss.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AAIController_Boss : public AAIController
{
	GENERATED_BODY()
public:
	AAIController_Boss();
	void RunBT();
	void StopBT();
private:


};
