// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"
#include "Component_Inventory.h"
#include"Components/ProgressBar.h"
#include"Components/TextBlock.h"
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
	
	RecoveryItemNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("RecoveryItemNum0")));
	
	GameTimer = 45.0f;
	PlayerHP = 100.0f;
	PlayerStamina = 100.0f;
	HPAmount = 0;
}
//연동된 character의 stat component에서 채력이 바뀔 때, 호출된다. 
void UGameWidget::UpdateCharacterStat()
{
	if (CurrentCharacterStat.IsValid())
	{
		/*if (PB_HP != nullptr)
			PB_HP->SetPercent(CurrentCharacterStat->GetHPRatio());*/
		/*if (HPAmount != nullptr)
		{
			HPAmount->
		}*/


		PlayerHP=CurrentCharacterStat->GetHP();
		float PlayerHPRatio = CurrentCharacterStat->GetHPRatio()*100.0f;

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

float UGameWidget::CheackTimeOut(float NewValue)
{
	if (NewValue == 0.0f)
	{
		//EGLOG(Error, TEXT("DIEEE"));
		CurrentCharacterStat->TakeDamage(100.0f);
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

	/*CurrentCharacterStat->HPChangedDelegate.AddLambda([this]()->void {
		if (CurrentCharacterStat.IsValid())
		{
			EGLOG(Warning, TEXT("HP : %f%"), CurrentCharacterStat->GetHPRatio());
		}
	});*/

	
}

void UGameWidget::BindCharacterInven(UComponent_Inventory * newInven)
{
	if (newInven == nullptr) {
		EGLOG(Error, TEXT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
		return;
	}
	//이미 설정 됐으면 튕긴다
	if (CurrenPlayerInventory!=nullptr) {
		EGLOG(Error, TEXT("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
		return;
	}
	EGLOG(Warning, TEXT("Player Post init compo4*************************************ns"));
	CurrenPlayerInventory = newInven;

}


float UGameWidget::GetGameTimer()
{
	//GameTimer= floorf(GameTimer * 100) / 100;
	return GameTimer;
}



