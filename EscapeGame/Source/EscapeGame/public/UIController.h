// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/PlayerController.h"
//#include "Blueprint/UserWidget.h"
#include "UIController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AUIController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay()override;
	/*virtual void NativeConstruct()override;

	UFUNCTION(BlueprintCallable)
		void StartNew();*/

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = UI)
		TSubclassOf<class UUserWidget>UserWidgetClass;
	UPROPERTY()
		class UUserWidget* UIWidgetInstance;
	/*UPROPERTY()
		class UButton* Btn_StartNew;*/
	
};
