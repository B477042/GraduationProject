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

void UTutorialWidget::Test(const FText & Txt1, const FText & Txt2)
{
	if (!Txt_NotifyTittle)
		EGLOG(Error, TEXT("txt notify nullptr"));
	if (!Txt_Describe)
		EGLOG(Error, TEXT("txt describe nullptr"));
	if (!Img_Gif)
		EGLOG(Error, TEXT("img gif nullptr"));

	Txt_NotifyTittle->SetText(Txt1);
	Txt_Describe->SetText(Txt2);

}
