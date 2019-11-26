// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"
#include"Components/ProgressBar.h"
#include"Components/TextBlock.h"
//#include"GameStat.h"

//void UGameWidget::BindCharacterStat(UGameStat * NewCharacterStat)
//{
//	if (NewCharacterStat == nullptr)return;
//	CurrentCharacterStat = NewCharacterStat;
//	
//}

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PB_HP = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPTEXT")));
	GameTimer = 60.0f;
	
}

void UGameWidget::UpdateCharacterStat()
{
	if(CurrentCharacterStat.IsValid())
		if(PB_HP!=nullptr)
			PB_HP->SetPercent(CurrentCharacterStat->GetHPRatio());
}

float UGameWidget::CheackTimeOut(float NewValue)
{
	return (NewValue >= 0.0f) ? NewValue: 0.0f;
}

void UGameWidget::TimeExtend(float addTime)
{
	GameTimer += addTime;
}

void UGameWidget::BindCharacterStat(const UCharacterStatComponent * newStat)
{
	if (newStat == nullptr) {
		EGLOG(Error, TEXT("No Character Stat Componenet"));
		return;
	}
	CurrentCharacterStat = newStat;
	CurrentCharacterStat->HPChangedDelegate.AddUObject(this, &UGameWidget::UpdateCharacterStat);
	CurrentCharacterStat->HPChangedDelegate.AddLambda([this]()->void {
		if (CurrentCharacterStat.IsValid())
		{
			EGLOG(Warning, TEXT("HP : %f%"), CurrentCharacterStat->GetHPRatio());
		}
	});

	
}

float UGameWidget::GetGameTimer()
{
	return GameTimer;
}



