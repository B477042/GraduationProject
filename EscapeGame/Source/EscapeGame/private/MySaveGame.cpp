// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaveGame.h"

UMySaveGame::UMySaveGame()
{
	SaveSlotName = TEXT("AutoSave");
	UserIndex = 0;
	WorldName = TEXT("Stage1");
	Level = 1;
	CurrentHP = 100;
	n_CardKey = -1;
	n_RecoveryItem = -1;
	LastLocation = FVector::ZeroVector;
	LastRotator = FRotator::ZeroRotator;

}

void UMySaveGame::ResetData()
{
	SaveSlotName = TEXT("AutoSave");
	UserIndex = 0;
	WorldName = TEXT("Stage1");
	Level = 1;
	CurrentHP = 100;
	n_CardKey = -1;
	n_RecoveryItem = -1;
	LastLocation = FVector::ZeroVector;
	LastRotator = FRotator::ZeroRotator;

}
