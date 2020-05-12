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
	//PB_HP = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	PB_Stamina = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaBar")));
	Img_Battery = Cast<UImage>(GetWidgetFromName(TEXT("HPImage")));
	Img_RecoveryItem = Cast<UImage>(GetWidgetFromName(TEXT("RecoveryItemImage")));
	//HPAmount = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPTEXT")));
	GameTimer = 60.0f;
	PlayerHP = 100.0f;
	PlayerStamina = 100.0f;
}
//연동된 character의 stat component에서 채력이 바뀔 때, 호출된다. 
void UGameWidget::UpdateCharacterStat()
{
	if (CurrentCharacterStat.IsValid())
	{
		/*if (PB_HP != nullptr)
			PB_HP->SetPercent(CurrentCharacterStat->GetHPRatio());*/
		/*if (HPAmount != nullptr)
		{
			HPAmount->
		}*/
		PlayerHP=CurrentCharacterStat->GetHP();
	}

}

void UGameWidget::UpdateStamina()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (PB_Stamina != nullptr)
			PB_Stamina->SetPercent(CurrentCharacterStat->GetStaminaRatio());
		PlayerStamina = CurrentCharacterStat->GetStamina();
	}
}

float UGameWidget::CheackTimeOut(float NewValue)
{
	return (NewValue >= 0.0f) ? NewValue: 0.0f;
}

void UGameWidget::TimeExtend(float addTime)
{
	GameTimer += addTime;
}

void UGameWidget::BindCharacterStat( UStatComponent_Player * newStat)
{
	if (newStat == nullptr) {
		EGLOG(Error, TEXT("No Character Stat Componenet"));
		return;
	}
	CurrentCharacterStat = newStat;
	CurrentCharacterStat->HPChangedDelegate.AddUObject(this, &UGameWidget::UpdateCharacterStat);
	CurrentCharacterStat->StaminaChangedDelegate.AddUObject(this, &UGameWidget::UpdateStamina);
	/*CurrentCharacterStat->HPChangedDelegate.AddLambda([this]()->void {
		if (CurrentCharacterStat.IsValid())
		{
			EGLOG(Warning, TEXT("HP : %f%"), CurrentCharacterStat->GetHPRatio());
		}
	});*/

	
}

float UGameWidget::GetGameTimer()
{
	//GameTimer= floorf(GameTimer * 100) / 100;
	return GameTimer;
}



