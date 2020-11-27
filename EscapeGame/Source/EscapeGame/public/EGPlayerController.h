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
	void ChangeInputMode(bool bGameMode = true);
	//UFUNCTION(BlueprintCallable)
	void OnGamePaused();
	void OnEnterPressed();
	void OnKillMode();

	void LoadTutorialMessage(const FName* MessageName,bool bIsImportant);


	class UGameWidget* GetHUDWidget()const;
	class UTutorialWidget* GetTutorialWidget()const;



	FOnKeyTest KeyInputTest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UGameWidget>HUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget>PAUSEWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UTutorialWidget>TutorialWidgetClass;
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget>BloodWidgetClass;*/


	void SyncStatToHUD();
	void IsMoveKeyPressed();
	const class UDataTable* GetDT_Player();
	const class UDataTable* GetDTTutorial();
	
	//Called Next Stage Event
	UFUNCTION(BlueprintCallable, Category = "Data")
		bool NextStage();

	UFUNCTION(BlueprintCallable, Category = "Store")
	void SaveGame(class UEGSaveGame* SaveInstance);
	UFUNCTION(BlueprintCallable, Category = "Store")
	void LoadGame(class UEGSaveGame* LoadInstance);

private:

	//void loadLocation();
	
	//void load

	UPROPERTY(meta=(AllowPrivateAccess=true))
		class UGameWidget* HUD;

	UPROPERTY()
		class UUserWidget* PauseUI;
	UPROPERTY(meta = (AllowPrivateAccess = true))
	class UTutorialWidget* TutorialWidget;

	//UPROPERTY()
	//	bool bIsPauseCalled;
	

	//Data Table For Player Stat
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DT_Player;
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DT_Tutorial;


	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
	FInputModeGameAndUI GameAndUIMode;

};
