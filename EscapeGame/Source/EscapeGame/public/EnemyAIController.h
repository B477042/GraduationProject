// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
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
		static const FName TargetPos;

		const class UBlackboardData* GetBlackBoard() { return BBData; }
			virtual	void RunAI();
	virtual	void StopAI();

	//Find Target Object's Location. If Target is nullptr, return false
	virtual bool GetTargetPlayerLocation(FVector& Retval);
	

protected:
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;
	virtual void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	

	void OnTakeDamaged(AActor* OtherActor);
 
	//Blackboard Data File Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBlackboardData* BBData;
	//Behavior Tree File Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BTData;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(AllowPrivateAccess=true))
	UEnvQuery *PathHelpersEQS;
	
};
