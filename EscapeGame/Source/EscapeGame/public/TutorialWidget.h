// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "EGGameInstance.h"
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

	UFUNCTION(BlueprintCallable)
	void ReceiveMessage( FText NotifyTittle,  FText Describe,FSoftObjectPath ObjectPath);
	UFUNCTION(BlueprintCallable)
		void OnButtonClicked();
protected:
	void AsyncImageLoad();
protected:
	UPROPERTY(BlueprintReadOnly)
		class UEditableText*  Txt_NotifyTittle;
	UPROPERTY(BlueprintReadOnly)
		class UEditableText*  Txt_Describe;
	UPROPERTY()
		class UImage* Img_Gif;
	UPROPERTY()
		class UButton* Btn_Close;

	FSoftObjectPath path_Object;
	const FLinearColor activateColor= FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	const FLinearColor deactivateColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);
};
