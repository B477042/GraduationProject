// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveInfoWidget.h"
#include "EGGameInstance.h"
#include "EGSaveGame.h"


void  USaveInfoWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	Txt_FileName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TXTFileName")));
	Txt_PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_PlayerLevel")));
	Txt_PlayerFury = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_PlayerFury")));
	Txt_PlayerHP = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_PlayerHP")));
	Txt_Remaintime = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_RemainTime")));
	Txt_StageName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StageName")));


}
void  USaveInfoWidget::NativeConstruct()
{
	
	Super::NativeConstruct();


}

bool USaveInfoWidget::LoadSaveData()
{
	auto GameInstance = Cast<UEGGameInstance>(GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("casting fail"));
		return false;
	}
	EGLOG(Error, TEXT("%s"), *ToLoadData.ToString());
	const auto  LoadInstance = Cast<UEGSaveGame>(UGameplayStatics::LoadGameFromSlot(ToLoadData.ToString(), 0));
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("Load Failed"));
		
		return false;
	}

	const auto PlayerData = LoadInstance->D_Player;
	const auto ProgressData = LoadInstance->GameProgressData;
	
	Txt_FileName->SetText(FText::FromName( ToLoadData));

	//Player Level
	FString TempString = FString::Printf(TEXT("Player Level : %d"),  PlayerData.Level);
	Txt_PlayerLevel->SetText(FText::FromString( TempString));
	//Player Fury
	TempString = FString::Printf(TEXT("Player Fury : %d"), PlayerData.Fury);
	Txt_PlayerFury->SetText(FText::FromString(TempString));
	//Player HP
	TempString = FString::Printf(TEXT("Player HP : %d"), PlayerData.Hp);
	Txt_PlayerHP->SetText(FText::FromString(TempString));
	//Player RemainTime
	TempString = FString::Printf(TEXT("Remain Time : %.2f"), ProgressData.RemainTimes);
	Txt_Remaintime->SetText(FText::FromString(TempString));
	//Player StageName
	TempString = FString::Printf(TEXT("Stage Name : %s"), *ProgressData.LevelName.ToString());
	Txt_StageName->SetText(FText::FromString(TempString));



	return true;
}
