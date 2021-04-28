// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAIController.h"
#include "EGSaveGame.h"
#include "AIController_Boss.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AAIController_Boss : public AEnemyAIController
{
	GENERATED_BODY()
public:
	AAIController_Boss();
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;

	virtual void RunAI()override;
	virtual void StopAI()override;

	//static FName Name_TargetPos;
	static FName ActionTimer;
	static FName IsDash;
	static FName MP;
	static FName BackStepPoint;
	static FName SoundPlayed;
	static FName BehaviorPattern;
	

	UFUNCTION(BlueprintCallable)
	void SaveGame(FBossData& BossData);
	UFUNCTION(BlueprintCallable)
	void LoadGame(const FBossData& BossData);


private:
	//UPROPERTY(VisibleAnywhere, Category = AI)
	//	class UBlackboardData* BBData;
	////Behavior Tree File Data
	//UPROPERTY(VisibleAnywhere, Category = AI)
	//	class UBehaviorTree* BTData;

	UPROPERTY(EditInstanceOnly, Category = "BlackBoard Data", meta = (AllowPrivateAccess = "true"))
		bool bIsDebugMode;
	UPROPERTY(EditInstanceOnly, Category = "BlackBoard Data", meta = (AllowPrivateAccess = "true"))
		float n_DetectRange;

};
