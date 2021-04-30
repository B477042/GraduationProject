// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
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

	//출력할 메시지를 받습니다
	void ReceiveTutorialMessage(const FText& NotifyTittle, const FText& Describe, const FText& GIFPath);

private:
	//Gif file image
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = true))
	UImage* GIF;	

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = true))
	UMultiLineEditableTextBox* Txt_Describe;
	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = true))
	UTextBlock* Txt_NotifyTittle;
};
