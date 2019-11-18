// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerController.h"
#include"GameWidget.h"
//#include"GameStat.h"


AEGPlayerController::AEGPlayerController()
{
	
	static ConstructorHelpers::FClassFinder<UGameWidget> UI_HUD_C(TEXT("/Game/MyFolder/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
	
}

void AEGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD = CreateWidget<UGameWidget>(this, HUDWidgetClass);
	HUD->AddToViewport();

	
	//PlayerStat = Cast<UGameStat>(PlayerStat);
	//if (PlayerStat == nullptr)return;
	//HUD->BindCharacterStat(PlayerStat);
	//
	EGLOG(Warning, TEXT("Controller begin play"));
}

void AEGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EGLOG(Warning, TEXT("Controller post initialize components"));
}

void AEGPlayerController::Possess(APawn * aPawn)
{
	Super::Possess(aPawn);
	EGLOG(Warning, TEXT("possessed complete") );
}



 UGameWidget* AEGPlayerController::GetHUDWidget() const
{
	return HUD;
}
