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
		return;
	}
	ContinueButton = Cast<UButton>(GetWidgetFromName("BTN_Continue"));
	if (ContinueButton == nullptr)
	{
		EGLOG(Error, TEXT("Continue Button is not vaild"));
		return;
	}

	TalkerBox = Cast<UEditableTextBox>(GetWidgetFromName("TalkerText"));
	if (TalkerBox == nullptr)
	{
		EGLOG(Error, TEXT("Talker Box is nullptr"));
		return;
	}
	
	
	

	NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextClicked);
	PrevButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnPrevClicked);
	ContinueButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnContinueClicked);
	bIsAllowToNext = true;

}



void UDialogueWidget::SetTalker(AActor * Other, FText Name)
{
	Talker = Other;
	
	TalkerBox->SetText(Name);
	
}

void UDialogueWidget::OnNextClicked()
{
	if (Talker == nullptr)
	{
		EGLOG(Error, TEXT("Who is Talker??"));
		return;
	}

	EGLOG(Error, TEXT("HITTTTTTTTTTTT"));
}

void UDialogueWidget::OnPrevClicked()
{
	if (Talker == nullptr)
	{
		EGLOG(Error, TEXT("Who is Talker??"));
		return;
	}

	EGLOG(Error, TEXT("RUNNNNNNNNN"));
}

void UDialogueWidget::OnContinueClicked()
{
	if (!bIsAllowToNext)return;
	UGameplayStatics::OpenLevel(this,"Stage1");
}
