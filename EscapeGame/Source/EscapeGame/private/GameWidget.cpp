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
//������ character�� stat component���� ä���� �ٲ� ��, ȣ��ȴ�. 
void UGameWidget::UpdateCharacterStat()
{
	if (CurrentCharacterStat.IsValid())
	{
		
		PlayerHP=CurrentCharacterStat->GetHP();
		float PlayerHPRatio = CurrentCharacterStat->GetHPRatio()*100.0f;
		float BlurRate = 0.5f*(1.0f - CurrentCharacterStat->GetHPRatio());


		//Ui �� ȿ��. ���� 2021 03 12
		//Img_Blood->SetBrushTintColor(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f,BlurRate )));
		//�̹������� BP���� �ҷ����� �͵��̴�
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

		//timer�� 0�� �Ǹ�
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
	//Card Key Item ó��
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
	//Recover Item ó��
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
//UI���� ���� �̹������� �ҷ��ɴϴ�
void UGameWidget::loadImages()
{
	//static ConstructorHelpers::FObjectFinder<UImage>(TEXT(""))
}

void UGameWidget::TimeExtend(float addTime)
{
	GameTimer += addTime;


	////15�� �̸��̸� ������
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
	//�̹� ���� ������ ƨ���
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



