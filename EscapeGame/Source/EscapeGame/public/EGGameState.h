// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EnemyCharacter.h"
#include "GameFramework/GameState.h"
#include "EGGameState.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTimeChanged, float, Time);


UCLASS(Config = "GameStateValue")
class ESCAPEGAME_API AEGGameState : public AGameState
{
	GENERATED_BODY()
public:
	AEGGameState();

protected:
	virtual void BeginPlay()override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
public:
	

	void SetTimer(float NewTimeValue);
	float GetRemainTimes() { return RemainTimes; }
	

	UFUNCTION(BlueprintCallable)
		virtual	void SaveGame(class UEGSaveGame* SaveInstance);
	 
	UFUNCTION(BlueprintCallable)
		virtual	void LoadGame(const class UEGSaveGame* LoadInstance);


protected:
	//Escape restriction time
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		float RemainTimes;

public:
	////Level에 존재하는 EnemyCharacter의 리스트
	//UPROPERTY(Transient, VisibleAnywhere, Category = "List", meta = (AllowPrivateAccess = "true"))
	//	TArray<TWeakObjectPtr<AEnemyCharacter>>A_Enemies;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString LevelName;

	
};
