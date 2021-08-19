// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeGameGameMode.h"
#include"EGPlayerCharacter.h"
#include"EGPlayerController.h"
#include "EGGameState.h"
#include"EGPlayerState.h"
//#include "DT_DataStruct.h"


AEscapeGameGameMode::AEscapeGameGameMode()
{
	DefaultPawnClass = AEGPlayerCharacter::StaticClass();
	PlayerControllerClass = AEGPlayerController::StaticClass();
	GameStateClass = AEGGameState::StaticClass();
	PlayerStateClass = AEGPlayerState::StaticClass();

}

void AEscapeGameGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AEscapeGameGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//EGGameState = Cast< AEGGameState>(GameState);
}
