// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "Components/Image.h"
#include "Components/EditableText.h"


void UTutorialWidget::NativeConstruct()
{

	Super::NativeConstruct();
	Txt_NotifyTittle = Cast<UEditableText>(GetWidgetFromName(TEXT("NotifyTittle")));
	Txt_Describe = Cast<UEditableText>(GetWidgetFromName(TEXT("Describe")));
	Img_Gif= Cast<UImage>(GetWidgetFromName(TEXT("ImageSpace")));


}

void UTutorialWidget::ReceiveMessage( FText  NotifyTittle,  FText  Describe)
{
	if (!Txt_NotifyTittle)
		EGLOG(Error, TEXT("txt notify nullptr"));
	if (!Txt_Describe)
		EGLOG(Error, TEXT("txt describe nullptr"));
	if (!Img_Gif)
		EGLOG(Error, TEXT("img gif nullptr"));

	auto strDia = Describe.ToString();
	int num = 0;
	if (strDia.FindChar('\\', num))
	{
		
		strDia.ReplaceInline(TEXT("\\n"), /*TEXT("opop")*/LINE_TERMINATOR);

		Describe = FText::FromString(strDia);
		
	}


	Txt_NotifyTittle->SetText(NotifyTittle);
	Txt_Describe->SetText(Describe);

}
