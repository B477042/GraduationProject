// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"



//Diagram 의 TEXT 내용
void UDialogueWidget::PrintLog(FText Diagram)
{
	if (!TextDiagram)return;
	//\n글자를 찾아서 엔터로 바꿔주는 작업
	auto strDia = Diagram.ToString();
	int num=0;
	if (strDia.FindChar('\\', num))
	{
		EGLOG(Error, TEXT("Find \\"));
		strDia.ReplaceInline(TEXT("\\n"), /*TEXT("opop")*/LINE_TERMINATOR);
		
		Diagram = FText::FromString(strDia);
		EGLOG(Error, TEXT("%s"), *Diagram.ToString());
		EGLOG(Error, TEXT("%s"), *strDia);
	}
	
		TextDiagram->SetText(Diagram);
		
		//TextDiagram->ColorAndOpacity_DEPRECATED;
		
			//FSlateColor::FSlateColor(FLinearColor::Blue);
		
		//FSlateColor newColor(FLinearColor::Blue);
		//TextDiagram->ColorAndOpacity_DEPRECATED.GetSpecifiedColor().Blue;
		//	Font_DEPRECATED = FSlateColor::FSlateColor(FLinearColor::Blue);
		

	

		//->SetText(Diagram);
//	EGLOG(Warning, *Diagram.ToString());

}

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
	TextDiagram = Cast<UEditableText>(GetWidgetFromName("Dialogue"));
	if (TalkerBox == nullptr)
	{
		EGLOG(Error, TEXT("TextDiagram is nullptr"));
		return;
	}
	
	
	

	NextButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnNextClicked);
	PrevButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnPrevClicked);
	ContinueButton->OnClicked.AddDynamic(this, &UDialogueWidget::OnContinueClicked);
	bIsAllowToNext = true;

}



void UDialogueWidget::SetTalkerName( FText Name)
{
	
	TalkerBox->SetText(Name);
	
}

void UDialogueWidget::OnNextClicked()
{
	/*if (Talker == nullptr)
	{
		EGLOG(Error, TEXT("Who is Talker??"));
		return;
	}*/
	OnClickNextDelegate.Broadcast();

	//EGLOG(Error, TEXT("HITTTTTTTTTTTT"));
}

void UDialogueWidget::OnPrevClicked()
{
	/*if (Talker == nullptr)
	{
		EGLOG(Error, TEXT("Who is Talker??"));
		return;
	}*/
	OnClickPrevDelegate.Broadcast();
	//TextDiagram->linercolor
	//EGLOG(Error, TEXT("RUNNNNNNNNN"));
}

void UDialogueWidget::OnContinueClicked()
{
	if (!bIsAllowToNext)return;
	OnClickSkipDelegate.Broadcast();

	

	UGameplayStatics::OpenLevel(this,NextStage);
}
