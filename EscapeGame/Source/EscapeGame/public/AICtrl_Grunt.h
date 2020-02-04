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

	static const FName TargetPlayer;
	static const FName HomePos;
	static const FName PatrolPos;

};
