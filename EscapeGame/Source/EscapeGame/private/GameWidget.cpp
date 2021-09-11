// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"
#include "Component_Inventory.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Component_Fury.h"
#include "Item_CardKey.h"
#include "Item_Recover.h"
#include "EGGameState.h"
//#include"GameStat.h"



void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//PB_HP = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	PB_Stamina = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaBar")));
	PB_Fury = Cast<UProgressBar>(GetWidgetFromName(TEXT("FuryBar")));
	Img_Battery = Cast<UImage>(GetWidgetFromName(TEXT("HPImage")));
	Img_RecoveryItem = Cast<UImage>(GetWidgetFromName(TEXT("RecoveryItemImage")));
	Img_Cardkey = Cast<UImage>(GetWidgetFromName(TEXT("img_Cardkey")));
	
	RecoveryItemNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("RecoveryItemNum0")));
	Txt_TimerBlock=Cast<UTextBlock>(GetWidgetFromName(TEXT("TimerBlock")));

	
	
	EGLOG(Error, TEXT("Test Widget"));
	GameTimer = 60.0f;
	
	PlayerHP = 100.0f;
	PlayerStamina = 100.0f;
	HPAmount = 0;
	FuryBarColor1 = FLinearColor::Black;
	FuryBarColor2 = FLinearColor::Red;


	Txt_TimerBlock->TextDelegate.BindUFunction(this, TEXT("BindingTimeText"));
	Txt_TimerBlock->ColorAndOpacityDelegate.BindUFunction(this, TEXT("BindingTimeColor"));
	 
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

void UGameWidget::UpdateFury(float Ratio)
{
	if (!CurrentPlayerFury.IsValid()||!PB_Fury)
	{
		EGLOG(Error, TEXT("Invalid"));
		return;
	}


	PB_Fury->SetPercent(Ratio);
	if (Ratio==1.0f)
	{
		
	}

	FLinearColor NewColor = FLinearColor::LerpUsingHSV(FuryBarColor1, FuryBarColor2, Ratio);
	PB_Fury->SetFillColorAndOpacity(NewColor );

}


float UGameWidget::CheackTimeOut(float NewValue)
{
	 
	if (NewValue <= 0.0f)
	{
		//EGLOG(Error, TEXT("DIEEE"));
		CurrentCharacterStat->TakeDamage(9.0f);
	 
	}
	

	return (NewValue >= 0.0f) ? NewValue: 0.0f;
}

FText UGameWidget::BindingTimeText()
{
	FText Retval;
	AEGGameState* GameState = Cast<AEGGameState>( UGameplayStatics::GetGameState());
	if (!GameState)
	{
		EGLOG(Error, TEXT("Game State Failed"));
		Retval = FText("State failed");
		return Retval;
	}
	


	return Retval;
}

FLinearColor UGameWidget::BindingTimeColor()
{
	FLinearColor Retval;
	return Retval;
}


void UGameWidget::TimeExtend(float addTime)
{
	GameTimer += addTime;

	
	//15초 미마이면 빨간색
	if (GameTimer < 15.0f)
	{
		
	
		Txt_TimerBlock->SetColorAndOpacity(FLinearColor::Red);
	}
	else if (GameTimer < 30.0f)
	{
		

		Txt_TimerBlock->SetColorAndOpacity(FLinearColor::Yellow);
	}
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
	//인벤토리의 델리게이트와 위젯 연동
	CurrentPlayerInventory->OnItemUpdated.BindUFunction(this, "UpdateItemes");

}

void UGameWidget::BindCharacterFury(UComponent_Fury* newFury)
{
	if (!newFury)
	{
		EGLOG(Error, TEXT("Component null"));
		return;
	}

	CurrentPlayerFury = newFury;
	//Bind Fury delegate
	CurrentPlayerFury->OnFuryChanged.BindUFunction(this, "UpdateFury");

}


float UGameWidget::GetGameTimer()
{
	
	return GameTimer;
}



