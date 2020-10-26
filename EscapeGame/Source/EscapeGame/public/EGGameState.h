// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EnemyCharacter.h"
#include "GameFramework/GameState.h"
#include "EGGameState.generated.h"

/**
 *
 */
UCLASS()
class ESCAPEGAME_API AEGGameState : public AGameState
{
	GENERATED_BODY()
public:
	AEGGameState();




	//���� loadgame���� ������ �����ϰ� �Ȱ������� üũ�Ѵ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		bool bIsLoadedGame;
	//Escape restriction time
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		float RemainTimes;


	//Level�� �����ϴ� EnemyCharacter�� ����Ʈ
	UPROPERTY(VisibleAnywhere, Category = "List", meta = (AllowPrivateAccess = "true"))
		TArray<TWeakObjectPtr<AEnemyCharacter>>A_Enemies;

	
};
