// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "EnemyAIController_Gunner.generated.h"

/**
 * 
 */
UCLASS(Config = "GameAi")
class ESCAPEGAME_API AEnemyAIController_Gunner : public AEnemyAIController
{
	GENERATED_BODY()

public:

	AEnemyAIController_Gunner();
protected:
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;
	
public:
	 void OnPossess(APawn* InPawn)override;
	 void OnUnPossess()override;
		

	virtual	void RunAI()override;
	virtual	void StopAI()override;
protected:
	
	UFUNCTION()
	virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	void SetUpAiPerception();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAISenseConfig_Sight * AiConfigSight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAISenseConfig_Hearing* AiConfigHearing;

	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "AiSense")
		float SightRadius;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "AiSense")
		float LoseSightRadius;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "AiSense")
		float PeripheralVisionAngleDegrees;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "AiSense")
		float HearingRange;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "AiSense")
		float LoSHearingRange;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "AiSense")
		float MaxAge;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "AiSense")
		uint8 bDetectFriendlies :1;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "AiSense")
		uint8 bDetectEnemies : 1;
	UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, Category = "AiSense")
		uint8 bDetectNeutrals : 1;

};
