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
	TimerText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TimerBlock")));
}

void UGameWidget::UpdateCharacterStat()
{
	if(PB_HP!=nullptr)
	PB_HP->SetPercent(90.0f);
}

void UGameWidget::UpdateTimerProgress()
{
}


