// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UGameWidget();
	//void BindCharacterStat(class UGameStat* NewCharacterStat);
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdateTimerProgress();
	
private:
	//TWeakObjectPtr<class UGameStat>CurrentCharacterStat;
	UPROPERTY()
		class UProgressBar* PB_HP;
	UPROPERTY()
		class UTextBlock* HPText;
	UPROPERTY()
		class UTextBlock* TimerText;
};
