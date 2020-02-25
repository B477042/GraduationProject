// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.generated.h"

/**
 * 
	Default AI Controller in My Game
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
		static const FName HomePos;
		static const FName PatrolPos;

		const class UDataTable* GetDT_Grunt();
protected:
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;
	
//private:
	virtual	void RunAI();
	virtual	void StopAI();
//private:
	//Blackboard Data File Data
	UPROPERTY(VisibleAnywhere,Category=AI)
		class UBlackboardData* BBData;
	//Behavior Tree File Data
	UPROPERTY(VisibleAnywhere, Category = AI)
		class UBehaviorTree* BTData;
	//Data Table for Grunt Enemy
	UPROPERTY(VisibleAnywhere, Category = DataTable)
	class UDataTable* DT_Grunt;
};
