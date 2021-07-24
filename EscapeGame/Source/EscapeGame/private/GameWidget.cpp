// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"
#include "Component_Inventory.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"

#include "Item_CardKey.h"
#include "Item_Recover.h"
//#include"GameStat.h"

//void UGameWidget::BindCharacterStat(UGameStat * NewCharacterStat)
//{
//	if (NewCharacterStat == nullptr)return;
//	CurrentCharacterStat = NewCharacterStat;
//	
//}

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//PB_HP = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	PB_Stamina = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaBar")));
	Img_Battery = Cast<UImage>(GetWidgetFromName(TEXT("HPImage")));
	Img_RecoveryItem = Cast<UImage>(GetWidgetFromName(TEXT("RecoveryItemImage")));
	Img_Cardkey = Cast<UImage>(GetWidgetFromName(TEXT("img_Cardkey")));
	Img_Blood= Cast<UImage>(GetWidgetFromName(TEXT("Img_Bloody")));
	RecoveryItemNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("RecoveryItemNum0")));
	//Txt_TimerBlock=Cast<UTextBlock>(GetWidgetFromName(TEXT("TimerBlock")));

	
	
	EGLOG(Error, TEXT("Test Widget"));
	GameTimer = 60.0f;
	RemainTime = GameTimer;
	PlayerHP = 100.0f;
	PlayerStamina = 100.0f;
	HPAmount = 0;
	
}
//연동된 character의 stat component에서 채력이 바뀔 때, 호출된다. 
void UGameWidget::UpdateCharacterStat()
{
	if (CurrentCharacterStat.IsValid())
	{
		
		PlayerHP=CurrentCharacterStat->GetHP();
		float PlayerHPRatio = CurrentCharacterStat->GetHPRatio()*100.0f;
		float BlurRate = 0.5f*(1.0f - CurrentCharacterStat->GetHPRatio());


		//Ui 피 효과. 제거 2021 03 12
		//Img_Blood->SetBrushTintColor(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f,BlurRate )));
		//이미지들은 BP에서 불러와진 것들이다
		if (PlayerHPRatio > 90.0f)
			Img_Battery->SetBrushFromTexture(Imgs_Battary[0]);
		else if (PlayerHPRatio >= 80.0f)
			Img_Battery->SetBrushFromTexture(Imgs_Battary[1]);
		else if(PlayerHPRatio>=60.0f)
			Img_Battery->SetBrushFromTexture(Imgs_Battary[2]);
		else if(PlayerHPRatio >=40.0f)
			Img_Battery->SetBrushFromTexture(Imgs_Battary[3]);
		else if(PlayerHPRatio >=20.0f)
			Img_Battery->SetBrushFromTexture(Imgs_Battary[4]);
		else if(PlayerHPRatio <=0.0f)
			Img_Battery->SetBrushFromTexture(Imgs_Battary[5]);

		//timer가 0이 되면
	/*	if (GameTimer <= 0.0f)
		{
			EGLOG(Error, TEXT("Time out"));
			CurrentCharacterStat->TakeDamage(200.0f);
		}*/

	}

}

void UGameWidget::UpdateStamina()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (PB_Stamina != nullptr)
			PB_Stamina->SetPercent(CurrentCharacterStat->GetStaminaRatio());
		PlayerStamina = CurrentCharacterStat->GetStamina();
	}
}

void UGameWidget::UpdateItemes(FName ItemName, int Amount)
{
	//Card Key Item 처리
	if(ItemName ==AItem_CardKey::Tag)
	{
		N_CardKeyItems = Amount;
		if(N_CardKeyItems<=0)
		{
			//Img_Cardkey->SetBrushFromTexture(Img_Cardkeys[0]);
		}
		else
		{
			//Img_Cardkey->SetBrushFromTexture(Img_Cardkeys[1]);
		}
		
	}
	//Recover Item 처리
	else if (ItemName==AItem_Recover::Tag)
	{
		N_RecoveryItems = Amount;
		RecoveryItemNum->SetText(FText::FromString(FString::FromInt(N_RecoveryItems)));
	}

	
}


float UGameWidget::CheackTimeOut(float NewValue)
{
	RemainTime = NewValue;
	if (NewValue <= 0.0f)
	{
		//EGLOG(Error, TEXT("DIEEE"));
		CurrentCharacterStat->TakeDamage(9.0f);
		EGLOG(Error, TEXT("TimeOUT"));
	}


	return (NewValue >= 0.0f) ? NewValue: 0.0f;
}
//UI에서 사용될 이미지들을 불러옵니다
void UGameWidget::loadImages()
{
	//static ConstructorHelpers::FObjectFinder<UImage>(TEXT(""))
}

void UGameWidget::TimeExtend(float addTime)
{
	GameTimer += addTime;


	////15초 미마이면 빨간색
	//if (GameTimer < 15.0f)
	//{
	//	FSlateColor RedColor(FLinearColor(1.0f,0.0f,0.0f,1.0f));
	//
	//	Txt_TimerBlock->SetColorAndOpacity(RedColor);
	//}
	//else if (GameTimer < 30.0f)
	//{
	//	FSlateColor YellowColor(FLinearColor(1.0f, 0.744f, 0.0f, 1.0f));

	//	Txt_TimerBlock->SetColorAndOpacity(YellowColor);
	//}
}

void UGameWidget::BindCharacterStat( UStatComponent_Player * newStat)
{
	if (newStat == nullptr) {
		EGLOG(Error, TEXT("No Character Stat Componenet"));
		return;
	}
	CurrentCharacterStat = newStat;
	CurrentCharacterStat->HPChangedDelegate.AddUObject(this, &UGameWidget::UpdateCharacterStat);
	CurrentCharacterStat->StaminaChangedDelegate.AddUObject(this, &UGameWidget::UpdateStamina);
	auto temp = Cast<ACharacter>(CurrentCharacterStat->GetOwner());
	if(temp)
		{
		OwnerChara = temp;
		}

	
	
}

void UGameWidget::BindCharacterInven(UComponent_Inventory * newInven)
{
	if (newInven == nullptr) {
		EGLOG(Error, TEXT("Inputed Param is nullptr"));
		return;
	}
	//이미 설정 됐으면 튕긴다
	if (CurrentPlayerInventory!=nullptr) {
		EGLOG(Error, TEXT("Inven comp is already setted "));
		return;
	}
	 
	CurrentPlayerInventory = newInven;

}


float UGameWidget::GetGameTimer()
{
	//GameTimer= floorf(GameTimer * 100) / 100;
	return GameTimer;
}



