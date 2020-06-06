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
	void OnKillMode();

	class UGameWidget* GetHUDWidget()const;

	FOnKeyTest KeyInputTest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UGameWidget>HUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget>PAUSEWidgetClass;



	void SyncStatToHUD();
	void IsMoveKeyPressed();
	const class UDataTable* GetDT_Player();

	UFUNCTION(BlueprintCallable, Category = "Data")
		void SaveGame();
	UFUNCTION(BlueprintCallable, Category = "Data")
		bool LoadGame();


private:

	void loadLocation();
	//void load

	UPROPERTY(meta=(AllowPrivateAccess=true))
		class UGameWidget* HUD;

	UPROPERTY()
		class UUserWidget* PauseUI;

	

	//Data Table For Player Stat
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DT_Player;


	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;

};
