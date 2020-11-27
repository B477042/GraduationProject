// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "UMG/Public/Components/Image.h"
#include "Components/MultiLineEditableTextBox.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;


private:
	//Gif file image
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = true))
	UImage* GIF;	

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = true))
	UMultiLineEditableTextBox* Describe;

	
};
