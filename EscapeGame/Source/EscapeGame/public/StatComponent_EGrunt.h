// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatComponent_Enemy.h"
#include "StatComponent_EGrunt.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UStatComponent_EGrunt : public UStatComponent_Enemy
{
	GENERATED_BODY()
public:

	UStatComponent_EGrunt();
	virtual void BeginPlay()override;

	virtual bool IsDead()override;

	virtual   void SaveGame(FEnemyData* SaveData)override;
	
	virtual  void LoadGame(const FEnemyData* LoadData)override;
protected:
	
	

	
private:
		//data table에서 level에 맞는 data를 가져온다
		void loadTypeData();
};
