// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include"CharacterStatComponent.h"
#include "GameWidget.generated.h"

/**
 * 
 */

//DECLARE_DELEGATE_OneParam(FBindStat,UCharacterStatComponent);

UCLASS()
class ESCAPEGAME_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UGameWidget();
	//void BindCharacterStat(class UGameStat* NewCharacterStat);
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void UpdateCharacterStat();

	UFUNCTION(BlueprintCallable)
		float CheackTimeOut(float NewValue);
	void BindCharacterStat(const UCharacterStatComponent* newStat);
	
	//FBindStat BindStatDelegate;

private:
	TWeakObjectPtr<class UCharacterStatComponent>CurrentCharacterStat;
	UPROPERTY()
		class UProgressBar* PB_HP;
	UPROPERTY()
		class UTextBlock* HPText;
	UPROPERTY()
		class UTextBlock* TimerText;
	UPROPERTY(BlueprintReadWrite, Category = Timer, Meta = (AllowPrivateAccess = true))
		float GameTimer;
	UPROPERTY(BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
		UCameraComponent* MiniMapCapture;
	
};
