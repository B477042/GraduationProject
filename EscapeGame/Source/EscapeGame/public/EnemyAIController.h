// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:

		AEnemyAIController();
		void OnPossess(APawn* InPawn)override;
		void OnUnPossess()override;

		static const FName TargetPlayer;
		
protected:
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;
	
private:
		void RunAI();
		void StopAI();
private:
	//Blackboard Data File Data
	UPROPERTY(VisibleAnywhere,Category=AI)
		class UBlackboardData* BBData;
	//Behavior Tree File Data
	UPROPERTY(VisibleAnywhere, Category = AI)
		class UBehaviorTree* BTData;
};
