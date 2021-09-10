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



}

void AEGGameState::SetTimer(float NewTimeValue)
{
	if (NewTimeValue < 0.0f)
	{
		NewTimeValue = 0.0f;
	}

	RemainTimes = NewTimeValue;
}
