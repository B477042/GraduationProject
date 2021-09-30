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
	Img_Cardkey = Cast<UImage>(GetWidgetFromName(TEXT("Image_CardKey")));
	
	RecoveryItemNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("RecoveryItemNum0")));
	Txt_TimerBlock=Cast<UTextBlock>(GetWidgetFromName(TEXT("TimerBlock")));

	
	
	DisplayTime = 0.0f;
	GameTimer = 60.0f;
	
	PlayerHP = 100.0f;
	PlayerStamina = 100.0f;
	HPAmount = 0;
	FuryBarColor1 = FLinearColor::Black;
	FuryBarColor2 = FLinearColor::Red;
 

	EGLOG(Error, TEXT("Wdiget Native Constructor"));

	Txt_TimerBlock->TextDelegate.BindUFunction(this, TEXT("BindingTimeText"));
	Txt_TimerBlock->ColorAndOpacityDelegate.BindUFunction(this, TEXT("BindingTimeColor"));


	/*static ConstructorHelpers::FObjectFinder<UTexture2D>Card0(TEXT(""));
	if (Card0.Succeeded())
	{
		Img_Cardkeys.Add(Card0.Object);
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D>Card1(TEXT(""));
	if (Card1.Succeeded())
	{
		Img_Cardkeys.Add(Card1.Object);
	}
	Texture2D'/Game/MyFolder/UI/img/1668933.1668933'
	Texture2D'/Game/MyFolder/UI/img/1668984.1668984'
	 */
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
			if (Img_Cardkeys[0] == nullptr)
			{
				EGLOG(Error, TEXT("Nullptr"));
				return;
			}
			Img_Cardkey->SetBrushFromTexture(Img_Cardkeys[0]);
		}
		else
		{
			if (Img_Cardkeys[1] == nullptr)
			{
				EGLOG(Error, TEXT("Nullptr"));
				return;
			}
			Img_Cardkey->SetBrushFromTexture(Img_Cardkeys[1]);
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


//Tick처럼 구동되는 점 확인
//BP에 바인딩 된 함수를 덮어서 실행 됨
FText UGameWidget::BindingTimeText()
{
	FText Retval;
	
	if (!OwnerChara.IsValid())
	{
		 
		EGLOG(Error, TEXT("OwnerActor is nullptr"));
		return Retval;
	}
	float PlayedTime = OwnerChara->GetController()->GetGameTimeSinceCreation();
	DisplayTime = GameTimer - PlayedTime;
	//EGLOG(Log, TEXT("Time : %f"), DisplayTime);
	//If Time Over
	if (DisplayTime <= 0)
	{
		FDamageEvent DamageEvent;
		OwnerChara->TakeDamage(100,DamageEvent,OwnerChara->GetController(), OwnerChara->GetController());
		DisplayTime = 0;
	}
	
	Retval = FText::AsNumber(DisplayTime);

	return Retval;
}

FLinearColor UGameWidget::BindingTimeColor()
{
	FLinearColor Retval;
	float TimePercent = DisplayTime / GameTimer;



	//Under 65%, Yellow, Under 20%, Red, else Green

	if (TimePercent < 0.65)
	{
		Retval = FLinearColor(1.000000, 0.421295, 0.000000, 1.000000);
	}
	
	else if (TimePercent < 0.2)
	{
		Retval = FLinearColor::Red;
	}
	else
	{
		Retval = FLinearColor::Green;
	}
	return Retval;
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
	if (!OwnerChara.IsValid())
	{
		OwnerChara = Cast<ACharacter>(newStat->GetOwner());
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



