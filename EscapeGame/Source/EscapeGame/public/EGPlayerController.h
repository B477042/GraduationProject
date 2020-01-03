// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/PlayerController.h"
#include "Components/SceneCaptureComponent2D.h"
#include "EGPlayerController.generated.h"

/**
 * 
 */



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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UGameWidget>HUDWidgetClass;


	void SyncStatToHUD();
private:
	UPROPERTY(meta=(AllowPrivateAccess=true))
		class UGameWidget* HUD;
	/*UPROPERTY()
		 USceneCaptureComponent2D* MapCam;*/
	/*UPROPERTY()
		class UGameStat* PlayerStat;*/
};
