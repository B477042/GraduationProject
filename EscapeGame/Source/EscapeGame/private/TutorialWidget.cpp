// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GIF = Cast<UImage>(GetWidgetFromName("img_GIF"));
	if (GIF == nullptr)
	{
		EGLOG(Error, TEXT("Fail to Find img_GIF from widget"));
		return;
	}

	Txt_Describe = Cast<UMultiLineEditableTextBox>(GetWidgetFromName("Describe"));
	if (Txt_Describe == nullptr)
	{
		EGLOG(Error, TEXT("Fail to Find Describe"));
		return;
	}
	Txt_NotifyTittle = Cast<UTextBlock>(GetWidgetFromName("NotifyTittle"));
	if (!Txt_NotifyTittle)
	{
		EGLOG(Error, TEXT("Fail to find NotifyTittle"));
		return;
	}

	EGLOG(Error, TEXT("Test Widget"));

}



void UTutorialWidget::ReceiveTutorialMessage(const FText & NotifyTittle, const FText & Describe, const FSoftObjectPath & GIFPath)
{
	Txt_NotifyTittle->SetText(NotifyTittle);
	Txt_Describe->SetText(Describe);




}
