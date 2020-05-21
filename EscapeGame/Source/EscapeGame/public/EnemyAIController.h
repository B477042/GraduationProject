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
		const class UBlackboardData* GetBlackBoard() { return BBData; }
		
protected:
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;
	
//private:
	virtual	void RunAI();
	virtual	void StopAI();
//private:
	//Blackboard Data File Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBlackboardData* BBData;
	//Behavior Tree File Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BTData;
	
};
