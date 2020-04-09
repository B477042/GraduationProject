// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/PlayerController.h"

#include"DialogueWidget.h"
#include "Tutorial_Controller.generated.h"

/**
 * 
 */


UCLASS()
class ESCAPEGAME_API ATutorial_Controller : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	ATutorial_Controller();

	virtual void BeginPlay()override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = UI)
		TSubclassOf<class UUserWidget>UserWidgetClass;
	UPROPERTY()
		class UUserWidget* UIWidgetInstance;
	
	

	/*UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = UI)
		UButton* BTN_Next;*/


};
