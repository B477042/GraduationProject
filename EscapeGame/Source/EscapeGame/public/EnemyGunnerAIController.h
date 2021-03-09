// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyGunnerAIController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AEnemyGunnerAIController : public AEnemyAIController
{
	GENERATED_BODY()

public:

	AEnemyGunnerAIController();
protected:
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;
	
public:
	 void OnPossess(APawn* InPawn)override;
	 void OnUnPossess()override;
		

	
protected:
	virtual	void RunAI()override;
	virtual	void StopAI()override;
	UFUNCTION()
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UAISenseConfig_Sight * AiConfigSight;


};
