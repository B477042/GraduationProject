// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialLogWidget.h"

#include "EGGameInstance.h"

void UTutorialLogWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Txt_NotifyTittle = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Tittle")));
	Txt_Describe = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("content")));
	ActiveTimer = 0.0f;
}

void UTutorialLogWidget::NativeTick(const FGeometry& Geometry,float InDeltaTime)
{
	Super::NativeTick(Geometry,InDeltaTime);

	if (!IsInViewport())
	{
		return;
	}

	ActiveTimer += InDeltaTime;

	if (ActiveTime <= ActiveTimer)
	{
		ActiveTimer = 0.0f;
		RemoveFromViewport();
	}

}

void UTutorialLogWidget::ReceiveMessage( FText& NotifyTittle, FText& Describe)
{
	//And Enter
	FString FixedDescribe = Describe.ToString();
	
	EGLOG(Log, TEXT("%s"), *NotifyTittle.ToString());
	EGLOG(Log, TEXT("%s"), *FixedDescribe);

	int num = 0;
	if (FixedDescribe.FindChar('\\', num))
	{

		FixedDescribe.ReplaceInline(TEXT("\\n"), /*TEXT("opop")*/LINE_TERMINATOR);

	}


	EGLOG(Log, TEXT("%s"), *NotifyTittle.ToString());
	EGLOG(Log, TEXT("%s"), *FixedDescribe);
	////Set Text
	FText NewDescribe= FText::FromString(FixedDescribe);
	EGLOG(Log, TEXT("%s"), *NewDescribe.ToString());
	if (!Txt_NotifyTittle)
	{
		EGLOG(Error, TEXT("nullptr"));
		return;
	}
	if (!Txt_Describe)
	{
		EGLOG(Error, TEXT("nullptr"));
		return;
	}

	Txt_NotifyTittle->SetText(NotifyTittle);
	Txt_Describe->SetText(FText::FromString( FString::Printf(TEXT("%s"), *FixedDescribe)));
	

}
	

