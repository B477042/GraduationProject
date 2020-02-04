// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "AICtrl_Grunt.generated.h"

/**
 * AI Controller For Grunt
 */
UCLASS()
class ESCAPEGAME_API AAICtrl_Grunt : public AEnemyAIController
{
	GENERATED_BODY()
public:
	AAICtrl_Grunt();


protected:
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;

	virtual void RunAI()override;
	virtual void StopAI()override;


};
