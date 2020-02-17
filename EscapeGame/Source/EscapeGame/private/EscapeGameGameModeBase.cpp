// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeGameGameModeBase.h"
#include"EGPlayerCharacter.h"
#include"EGPlayerController.h"
//#include "DT_DataStruct.h"


AEscapeGameGameModeBase::AEscapeGameGameModeBase()
{
	DefaultPawnClass = AEGPlayerCharacter::StaticClass();
	PlayerControllerClass = AEGPlayerController::StaticClass();


}

void AEscapeGameGameModeBase::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
