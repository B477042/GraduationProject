// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/GameState.h"
#include "EGGameState.generated.h"

/**
 * GameState is a subclass of GameStateBase that behaves like a multiplayer match-based game.
 * It is tied to functionality in GameMode.
 */

class UEGAttributeSetBase;

UCLASS(Config = "GameStateValue")
class ESCAPEGAME_API AEGGameState : public AGameState
{
	GENERATED_BODY()
public:
	AEGGameState();

protected:
	virtual void BeginPlay()override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	

	//void SetRemainTimes(float NewValue);
	//float GetRemainTimes() { return  RemainTimes; }
	//
	
protected:
	//Escape restriction time
	UPROPERTY(BlueprintReadWrite, Config, Transient, VisibleAnywhere, Category = "Data")
		float RemainTimes;

	
public:
	////Level�� �����ϴ� EnemyCharacter�� ����Ʈ
	//UPROPERTY(Transient, VisibleAnywhere, Category = "List", meta = (AllowPrivateAccess = "true"))
	//	TArray<TWeakObjectPtr<AEnemyCharacter>>A_Enemies;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString LevelName;

	
};
