// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:


protected:
	virtual void NativeConstruct()override;

protected:
	UPROPERTY()
		class UButton* NextButton;
	UPROPERTY()
		class UButton* PrevButton;

	
		
private:
	UFUNCTION()
		void OnNextClicked();
	UFUNCTION()
		void OnPrevClicked();


};
