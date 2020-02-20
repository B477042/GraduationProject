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

	virtual void PostInitializeComponents()override;
	virtual void OnPossess(APawn* aPawn)override;
	

	class UGameWidget* GetHUDWidget()const;

	FOnKeyTest KeyInputTest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UGameWidget>HUDWidgetClass;


	void SyncStatToHUD();
	void IsMoveKeyPressed();
	const class UDataTable* GetDT_Player();

private:
	UPROPERTY(meta=(AllowPrivateAccess=true))
		class UGameWidget* HUD;

	//Data Table For Player Stat
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DT_Player;
	/*UPROPERTY()
		 USceneCaptureComponent2D* MapCam;*/
	/*UPROPERTY()
		class UGameStat* PlayerStat;*/
};
