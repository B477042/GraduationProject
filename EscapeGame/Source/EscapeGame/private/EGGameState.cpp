// Fill out your copyright notice in the Description page of Project Settings.


#include "EGGameState.h"

AEGGameState::AEGGameState()
{
	
	RemainTimes = 0.0f;
	//EGameState = EEGGameState::E_NewGame;
	LevelName = TEXT("Default");

}

void AEGGameState::BeginPlay()
{
	Super::BeginPlay();

}

void AEGGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AEGGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (RemainTimes > 0)
	{
		RemainTimes -= DeltaSeconds;
		OnTimeChanged.Execute(RemainTimes);

	}
	

}

void AEGGameState::SetTimer(float NewTimeValue)
{
	if (NewTimeValue < 0.0f)
	{
		NewTimeValue = 0.0f;
	}

	RemainTimes = NewTimeValue;
	OnTimeChanged.Execute(RemainTimes);
}

void AEGGameState::AddTime(float Value)
{

	RemainTimes += Value;
	OnTimeChanged.Execute(RemainTimes);
}

void AEGGameState::SaveGame(UEGSaveGame* SaveInstance)
{
	if (!SaveInstance)
	{
		return;
	}

	SaveInstance->GameProgressData.RemainTimes = RemainTimes;
}

void AEGGameState::LoadGame(const UEGSaveGame* LoadInstance)
{
	if (!LoadInstance)
	{
		return;

	}
	RemainTimes = LoadInstance->GameProgressData.RemainTimes;

}
