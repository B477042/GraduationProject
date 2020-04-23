// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial_Controller.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.h"

void ATutorial_Controller::BeginPlay()
{

	Super::BeginPlay();

	static ConstructorHelpers::FClassFinder<UUserWidget>WIDGET(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_Dialogue.UI_Dialogue_C'"));
	if (WIDGET.Succeeded())
	{
		UserWidgetClass = WIDGET.Class;
	}

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


	

	//UserWidgetClass.Get()->FindPropertyByName();

	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
	

	

}

void ATutorial_Controller::FindTalkers()
{
	bool bIsSucceed = false;

	auto Actors =GetWorld()->GetCurrentLevel()->Actors;

	for (int i = 0; i < Actors.Num(); i++)
	{
		auto it = Actors[i];

		//it.getcomponent

	}
}
