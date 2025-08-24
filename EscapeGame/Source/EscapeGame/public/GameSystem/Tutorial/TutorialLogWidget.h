// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "TutorialLogWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UTutorialLogWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float InDeltaTime)override;
	UFUNCTION(BlueprintCallable)
		void ReceiveMessage( FText& NotifyTittle,  FText& Describe);
protected:

	

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		UEditableTextBox* Txt_NotifyTittle;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		UEditableTextBox* Txt_Describe;
	
	
	const float ActiveTime=7.0f;
	float ActiveTimer;

};
