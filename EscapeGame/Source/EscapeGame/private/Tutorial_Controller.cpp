// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial_Controller.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.h"

ATutorial_Controller::ATutorial_Controller()
{



}


void ATutorial_Controller::BeginPlay()
{

	Super::BeginPlay();

	if (UserWidgetClass == nullptr) {
		EGLOG(Error, TEXT("UserWidgetClass is nullptr"));
		return;
	}

	UIWidgetInstance = CreateWidget <UUserWidget>(this, UserWidgetClass);
	if (UIWidgetInstance == nullptr)
	{
		EGLOG(Error, TEXT("Dialogue widget instance is nullptr"));
		return;
	}


	//static ConstructorHelpers::FClassFinder<UUserWidget>WIDGET(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_Dialogue.UI_Dialogue_C'"));
	//if (WIDGET.Succeeded())
	//{
	//	UserWidgetClass = WIDGET.Class;
	//}
	

	//UserWidgetClass.Get()->FindPropertyByName();

	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
	

	

}


