// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerController.h"
#include"GameWidget.h"
//#include""
#include"EGPlayerCharacter.h"
#include "..\public\EGPlayerController.h"
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
	SyncStatToHUD();
	EGLOG(Warning, TEXT("Controller begin play"));

	KeyInputTest.AddUObject(this,&AEGPlayerController::IsMoveKeyPressed);
	
	EGLOG(Warning, TEXT("Current Game Mode : %s"), *GetWorld()->GetFirstPlayerController()->GetName());
	
	FInputModeGameOnly GameOnly;
	SetInputMode(GameOnly);
}

void AEGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EGLOG(Warning, TEXT("Controller post initialize components"));
	
}

void AEGPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);
	
	EGLOG(Warning, TEXT("possessed complete") );
}



 UGameWidget* AEGPlayerController::GetHUDWidget() const
{
	return HUD;
}

 void AEGPlayerController::SyncStatToHUD()
 {
	 auto player = Cast<AEGPlayerCharacter>(GetCharacter());
	 if (player==nullptr)
	 {
		 EGLOG(Error, TEXT("Dynamic failed"));
		 return;
	 }
	 HUD->BindCharacterStat(player->GetStatComponent());
	
	 
 }

void AEGPlayerController::IsMoveKeyPressed()
 {
	//inputkey
	 if (IsInputKeyDown(EKeys::A))
	 {
		 EGLOG(Warning, TEXT("A Pressed"));
		 //return true;
	 }
	 else if (IsInputKeyDown(EKeys::S))
	 {
		 EGLOG(Warning, TEXT("S Pressed"));
	 }
	 else if (IsInputKeyDown(EKeys::D))
	 {
		 EGLOG(Warning, TEXT("D Pressed"));
	 }
	 else if (IsInputKeyDown(EKeys::W))
	 {
		 EGLOG(Warning, TEXT("W Pressed"));
	 }
	
	 
	// return false;
 }

 
