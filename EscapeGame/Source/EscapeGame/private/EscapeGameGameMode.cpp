// Fill out your copyright notice in the Description page of Project Settings.


//#include "DT_DataStruct.h"


#include "UnrealCore/EscapeGameGameMode.h"

#include "Actor/Character/EGPlayerCharacter.h"
#include "Actor/Character/EGPlayerController.h"
#include "UnrealCore/EGGameState.h"
#include "UnrealCore/EGPlayerState.h"

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
