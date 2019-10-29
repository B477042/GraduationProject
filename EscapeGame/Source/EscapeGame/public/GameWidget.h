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

	UFUNCTION(BlueprintCallable)
		float CheackTimeOut(float NewValue);
	
private:
	//TWeakObjectPtr<class UGameStat>CurrentCharacterStat;
	UPROPERTY()
		class UProgressBar* PB_HP;
	UPROPERTY()
		class UTextBlock* HPText;
	UPROPERTY()
		class UTextBlock* TimerText;
	UPROPERTY(BlueprintReadWrite, Category = Timer, Meta = (AllowPrivateAccess = true))
		float GameTimer;
};
