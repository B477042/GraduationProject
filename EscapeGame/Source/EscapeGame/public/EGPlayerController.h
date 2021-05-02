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

	

	class UGameWidget* GetHUDWidget()const;




	FOnKeyTest KeyInputTest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UGameWidget>HUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget>PAUSEWidgetClass;
	




	void SyncStatToHUD();
	void IsMoveKeyPressed();
	const class UDataTable* GetDT_Player();

	
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

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = true))
		class UGameWidget* HUD;


	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = true))
		class UUserWidget* PauseUI;




	//UPROPERTY()
	//	bool bIsPauseCalled;
	

	//Data Table For Player Stat
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DT_Player;
	




	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
	FInputModeGameAndUI GameAndUIMode;

};
