// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemyCharacter.h"
#include "EnermyBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AEnermyBossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:

	AEnermyBossCharacter();

private:
	void initComponents();
	void loadAsset();

private:
	

};
