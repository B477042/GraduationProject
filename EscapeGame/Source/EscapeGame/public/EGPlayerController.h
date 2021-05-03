// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/PlayerController.h"
#include "Components/SceneCaptureComponent2D.h"

#include "EGPlayerController.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnKeyTest);


UCLASS()
class ESCAPEGAME_API AEGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEGPlayerController();
	void BeginPlay();
	void SetupInputComponent()override;

	virtual void PostInitializeComponents()override;
	virtual void OnPossess(APawn* aPawn)override;
	UFUNCTION(BlueprintCallable)
		//If true, GameInputMode. False Game And UI Mode
	void ChangeInputMode(bool bGameMode = true);
	//UFUNCTION(BlueprintCallable)
	void OnGamePaused();
	void OnEnterPressed();
	void OnKillMode();

	

	class UGameWidget* GetHUDWidget()const;


	


	void SyncStatToHUD();
	void IsMoveKeyPressed();
	const class UDataTable* GetDT_Player();
	FOnKeyTest KeyInputTest;
	
	//Called Next Stage Event
	UFUNCTION(BlueprintCallable, Category = "Data")
		bool NextStage();

	UFUNCTION(BlueprintCallable, Category = "Store")
	void SaveGame(class UEGSaveGame* SaveInstance);
	UFUNCTION(BlueprintCallable, Category = "Store")
	void LoadGame(class UEGSaveGame* LoadInstance);


	void ShowTutorialMessage(uint8 TutorialMessage);
	void CloseTutorialMessage();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UGameWidget>HUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget>PAUSEWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UTutorialWidget>TUTOWidgetClass;

	//Viewport Priority
	const uint8 VP_HUD = 1;
	//Viewport Priority
	const uint8 VP_Tutorial = 2;
	//Viewport Priority
	const uint8  VP_Pause = 3;

private:

	//void loadLocation();
	
	//void load

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = true))
		class UGameWidget* HUD;

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = true))
		class UUserWidget* PauseUI;
	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = true))
		class UTutorialWidget* TutorialUI;


	//UPROPERTY()
	//	bool bIsPauseCalled;
	
	//Data Table For Player Stat
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DT_Player;
	//Tutorial Message Data table
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
		class UDataTable* DT_Tutorial;




	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
	FInputModeGameAndUI GameAndUIMode;

};
