// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "AnimatedTexture2D.h"
#include "Engine/Texture2D.h"
#include "EGPlayerController.h"

void UTutorialWidget::NativeConstruct()
{

	Super::NativeConstruct();
	Txt_NotifyTittle = Cast<UEditableText>(GetWidgetFromName(TEXT("NotifyTittle")));
	Txt_Describe = Cast<UEditableText>(GetWidgetFromName(TEXT("Describe")));
	Img_Gif= Cast<UImage>(GetWidgetFromName(TEXT("ImageSpace")));
	Btn_Close = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));

	//Btn_Close->OnClicked.AddDynamic(this, &UTutorialWidget::OnButtonClicked);

}

void UTutorialWidget::ReceiveMessage( FText  NotifyTittle,  FText  Describe, FSoftObjectPath ObjectPath)
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
	auto gameInstance = Cast< UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!gameInstance)return;

	path_Object = ObjectPath;

	EGLOG(Error, TEXT("%s"),*path_Object.GetAssetPathString());
	
	auto returnvalue = gameInstance->StreamableManager.RequestAsyncLoad(ObjectPath, FStreamableDelegate::CreateUObject(this,&UTutorialWidget::AsyncImageLoad));

	if (!returnvalue)
	{
		EGLOG(Error, TEXT("Fail to load"));
	}
	
	Txt_NotifyTittle->SetText(NotifyTittle);
	Txt_Describe->SetText(Describe);

}

void UTutorialWidget::OnButtonClicked()
{
	if (IsInViewport())
		RemoveFromViewport();
	

	auto controller = Cast<AEGPlayerController>(GetOwningPlayer());
	if (controller)
	{
		controller->CloseTutorialMessage();
	}



}
void UTutorialWidget::AsyncImageLoad()
{
	

	TSoftObjectPtr<UAnimatedTexture2D> ImageAsset(path_Object);
	UAnimatedTexture2D* newImage = ImageAsset.Get();
	if (newImage)
	{
		auto temp = Cast<UTexture>(newImage);
		if (!temp)
		{
			EGLOG(Error, TEXT("castubg fialse"));
			return;
		}

		

		Img_Gif->SetBrushResourceObject(temp);
		//EGLOG(Error, TEXT("good"));
	}
	else
		EGLOG(Error, TEXT("failed"));


}