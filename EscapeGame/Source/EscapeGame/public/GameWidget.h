// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "StatComponent_Player.h"
#include "GameWidget.generated.h"

/**
 * HUD System Class
 * Main UI for Player
 * Display Timer and MiniMap, HP
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
	void TimeExtend(float addTime);
	void BindCharacterStat( UStatComponent_Player* newStat);
	float GetGameTimer();
	//FBindStat BindStatDelegate;
	
	UFUNCTION(BlueprintCallable)
		void UpdateCharacterStat();

	UFUNCTION(BlueprintCallable)
		float CheackTimeOut(float NewValue);
private:
	TWeakObjectPtr<class UStatComponent_Player>CurrentCharacterStat;
	UPROPERTY()
		class UProgressBar* PB_HP;
	//UPROPERTY()
	//	class UTextBlock* HPAmount;//Write 'HP'
	//
	//UPROPERTY()
	//	class UTextBlock* TimerText;
	UPROPERTY(BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float PlayerHP;

	UPROPERTY(BlueprintReadWrite, Category = Timer, Meta = (AllowPrivateAccess = true))
		float GameTimer;

	UPROPERTY(BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
		UCameraComponent* MiniMapCapture;
	
};
