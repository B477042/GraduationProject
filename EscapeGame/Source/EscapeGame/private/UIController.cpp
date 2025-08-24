// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Controller/UIController.h"

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
void AUIController::BeginPlay()
{
	Super::BeginPlay();

	if (UserWidgetClass == nullptr) {
		EGLOG(Error, TEXT("UserWidgetClass is nullptr"));
		return;
	}
	UIWidgetInstance = CreateWidget <UUserWidget>(this, UserWidgetClass);
	if (UIWidgetInstance == nullptr)
	{
		EGLOG(Error, TEXT("UIWidgetInstance is nullptr"));
		return;
	}
	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}

