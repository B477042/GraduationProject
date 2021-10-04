// Fill out your copyright notice in the Description page of Project Settings.


#include "EGGameState.h"
#include "EGGameInstance.h"

AEGGameState::AEGGameState()
{
	 
	RemainTimes = 60.0f;
	//EGameState = EEGGameState::E_NewGame;
	LevelName = TEXT("Default");

}

void AEGGameState::BeginPlay()
{
	Super::BeginPlay();

	UEGGameInstance* const GameInstance = Cast<UEGGameInstance>(GetGameInstance());
	if(!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Game Instance cast failed"));
		return;
	}

	//GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AEGGameState::SaveGame);
	//GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AEGGameState::LoadGame);

}

void AEGGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

//void AEGGameState::SetRemainTimes(float NewValue)
//{
//	RemainTimes = NewValue;
//}
//
//
// 


