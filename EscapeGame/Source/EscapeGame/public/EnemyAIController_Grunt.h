// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController_Grunt.generated.h"

/**
 * AI Controller For Grunt
 */
UCLASS()
class ESCAPEGAME_API AEnemyAIController_Grunt : public AEnemyAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController_Grunt();

	const class UDataTable* GetDT_Grunt();

	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;
	UFUNCTION(BlueprintCallable)
	virtual void RunAI()override;
	UFUNCTION(BlueprintCallable)
	virtual void StopAI()override;
protected:
	UFUNCTION()
		virtual void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	//Data Table for Grunt Enemy
	UPROPERTY(VisibleAnywhere, Category = DataTable)
		class UDataTable* DT_Grunt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UAISenseConfig_Sight* AiConfigSight;

};
