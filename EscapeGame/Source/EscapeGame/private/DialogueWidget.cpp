// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"




void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PrevButton = Cast<UButton>(GetWidgetFromName("BTN_Prev"));
	if (PrevButton == nullptr)
	{
		EGLOG(Error, TEXT("Prev Button is not vaild"));
		return;
	}
	NextButton = Cast<UButton>(GetWidgetFromName("BTN_Next"));
	if(NextButton==nullptr)
	{
		EGLOG(Error, TEXT("NextButton is Not vaild"));
	}

	NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextClicked);
	PrevButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnPrevClicked);

}

void UDialogueWidget::OnNextClicked()
{
	EGLOG(Error, TEXT("HITTTTTTTTTTTT"));
}

void UDialogueWidget::OnPrevClicked()
{
	EGLOG(Error, TEXT("RUNNNNNNNNN"));
}
