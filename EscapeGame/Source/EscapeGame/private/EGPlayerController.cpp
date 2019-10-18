// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerController.h"

void AEGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEGPlayerController::Possess(APawn * aPawn)
{
	Super::Possess(aPawn);
	EGLOG(Warning, TEXT("possessed complete") );

}
