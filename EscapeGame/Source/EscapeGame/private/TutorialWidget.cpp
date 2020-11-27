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

	Describe = Cast<UMultiLineEditableTextBox>(GetWidgetFromName("txt_Describe"));
	if (Describe == nullptr)
	{
		EGLOG(Error, TEXT("Fail to Find txt_Describe"));
		return;
	}


}