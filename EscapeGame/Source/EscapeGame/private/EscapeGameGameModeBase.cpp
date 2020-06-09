// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeGameGameModeBase.h"
#include"EGPlayerCharacter.h"
#include"EGPlayerController.h"
#include "EGGameState.h"
//#include "DT_DataStruct.h"


AEscapeGameGameModeBase::AEscapeGameGameModeBase()
{
	DefaultPawnClass = AEGPlayerCharacter::StaticClass();
	PlayerControllerClass = AEGPlayerController::StaticClass();
	//GameStateClass = AEGGameState::StaticClass();


}

void AEscapeGameGameModeBase::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AEscapeGameGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//EGGameState = Cast< AEGGameState>(GameState);
}
