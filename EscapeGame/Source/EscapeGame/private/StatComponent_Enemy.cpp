// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/StatComponent_Enemy.h"
#include "UnrealCore/SaveGame/EGSaveGame.h"



UStatComponent_Enemy::UStatComponent_Enemy()
{
	MinWalkingSpeed = 0.0f;
	MaxWalkingSpeed = 350.0f;
	MaxRunningSpeed = 700.0f;
	Type = 0;
}

void UStatComponent_Enemy::InitializeComponent()
{
	Super::InitializeComponent();
}

void UStatComponent_Enemy::BeginPlay()
{
	Super::BeginPlay();

}

void UStatComponent_Enemy::SaveGame(FEnemyData* SaveData)
{
	if (!SaveData)
	{
		EGLOG(Error, TEXT("Save Data is nullptr"));
		return;
	}


	
	SaveData->Hp = CurrentHP;
}

void UStatComponent_Enemy::LoadGame(const FEnemyData* LoadData)
{
	if (!LoadData)
	{
		EGLOG(Error, TEXT(" LoadData is nullptr"));
		return;
	}
	 CurrentHP= LoadData->Hp;
}

void UStatComponent_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UStatComponent_Enemy::GetDropExp()
{
	return DropExp;
}

void UStatComponent_Enemy::SetType(int32 input)
{
	Type = input;
}



