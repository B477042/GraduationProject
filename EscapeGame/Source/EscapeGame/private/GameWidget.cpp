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
#include "Component_TimeLimit.h"
#include "Component_Stamina.h"
//#include"GameStat.h"



void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//PB_HP = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	PB_Stamina = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaBar")));
	PB_Fury = Cast<UProgressBar>(GetWidgetFromName(TEXT("FuryBar")));
	PB_Exp = Cast<UProgressBar>(GetWidgetFromName(TEXT("ExpBar")));
	Img_Battery = Cast<UImage>(GetWidgetFromName(TEXT("HPImage")));
	Img_RecoveryItem = Cast<UImage>(GetWidgetFromName(TEXT("RecoveryItemImage")));
	Img_Cardkey = Cast<UImage>(GetWidgetFromName(TEXT("Image_CardKey")));
	Txt_CardKey = Cast<UTextBlock>(GetWidgetFromName(TEXT("CardKeyText")));
	RecoveryItemNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("RecoveryItemNum0")));
	Txt_TimerBlock=Cast<UTextBlock>(GetWidgetFromName(TEXT("TimerBlock")));
	Txt_Level= Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelText")));
	
	
	DisplayTime = 0.0f;
	
	
	PlayerHP = 100.0f;
	//PlayerStamina = 100.0f;
	HPAmount = 0;
	FuryBarColor1 = FLinearColor::Black;
	FuryBarColor2 = FLinearColor::Red;
 

	EGLOG(Error, TEXT("Wdiget Native Constructor"));

	/*Txt_TimerBlock->TextDelegate.BindUFunction(this, FName("BindingTimeText"));
	Txt_TimerBlock->ColorAndOpacityDelegate.BindUFunction(this, FName("BindingTimeColor"));*/


}

void UGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}


//연동된 character의 stat component에서 채력이 바뀔 때, 호출된다. 
void UGameWidget::UpdateCharacterStat()
{
	if (CurrentPlayerStat.IsValid())
	{
		
		PlayerHP=CurrentPlayerStat->GetHP();
		float PlayerHPRatio = CurrentPlayerStat->GetHPRatio()*100.0f;
		float BlurRate = 0.5f*(1.0f - CurrentPlayerStat->GetHPRatio());


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
			CurrentPlayerStat->TakeDamage(200.0f);
		}*/

	}

}

void UGameWidget::UpdateStamina()
{
	if (CurrentPlayerStat.IsValid())
	{
		if (PB_Stamina != nullptr)
			PB_Stamina->SetPercent(CurrentPlayerStamina->GetStaminaRatio());
		//PlayerStamina = CurrentPlayerStat->GetStamina();
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
			
			Txt_CardKey->SetColorAndOpacity(FLinearColor::White);
			Img_Cardkey->SetBrushFromTexture(Img_Cardkeys[0]);
		}
		else
		{
			
			Txt_CardKey->SetColorAndOpacity(FLinearColor::Green);
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
		PB_Fury->SetFillColorAndOpacity(FLinearColor::Yellow);
		return;
	}

	FLinearColor NewColor = FLinearColor::LerpUsingHSV(FuryBarColor1, FuryBarColor2, Ratio);
	PB_Fury->SetFillColorAndOpacity(NewColor );

}

void UGameWidget::UpdateExp()
{
	if (CurrentPlayerStat.IsValid())
	{
		float Ratio = CurrentPlayerStat->GetExpRatio();
		PB_Exp->SetPercent(Ratio);
		EGLOG(Error, TEXT("EXP!! : %f"),Ratio);
	}
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
	if (!CurrentPlayerTimeLimit.IsValid())
	{
		return Retval;
	}
	DisplayTime = CurrentPlayerTimeLimit->GetCurrentRemainTime();
	
	
	

	Retval = FText::AsNumber(DisplayTime);

	return Retval;
}

FLinearColor UGameWidget::BindingTimeColor()
{
	FLinearColor Retval;
	if (!OwnerChara.IsValid())
	{

		EGLOG(Error, TEXT("OwnerActor is nullptr"));
		return Retval;
	}

	




	//Under 30, Yellow, Under 15, Red, else Green
	if (DisplayTime < 15.0f)
	{
		Retval = FLinearColor::Red;
	}
	else if (DisplayTime < 30.0f)
	{
		Retval = FLinearColor(1.000000, 0.421295, 0.000000, 1.000000);
	}	
	else
	{
		Retval = FLinearColor::Green;
	}
	return Retval;
}



void UGameWidget::NativeDestruct()
{
	Super::NativeDestruct();
	////CurrentPlayerStat.Get();
	////CurrentPlayerFury.Get();
	////CurrentPlayerInventory.Get();
	//GameState.Get();
}



void UGameWidget::BindCharacterStat( UStatComponent_Player * newStat)
{
	if (newStat == nullptr) {
		EGLOG(Error, TEXT("No Character Stat Componenet"));
		return;
	}
	CurrentPlayerStat = newStat;
	CurrentPlayerStat->HPChangedDelegate.AddUObject(this, &UGameWidget::UpdateCharacterStat);
	//CurrentPlayerStat->StaminaChangedDelegate.BindUObject(this, &UGameWidget::UpdateStamina);
	CurrentPlayerStat->OnExpChanged.BindUObject(this, &UGameWidget::UpdateExp);

	//========================================================
	//Level Text Update Lambda
	CurrentPlayerStat->OnLevelUP.BindLambda([this]()->void {
		int32 Level = CurrentPlayerStat->GetLevel();
		FString LevelText;
		if (Level < 10)
		{
			LevelText = TEXT("Lv 0")+FString::FromInt(Level);
			EGLOG(Log, TEXT("Level Text %s"), *LevelText);
		}
		else
		{
			LevelText = TEXT("Lv 0") + FString::FromInt(Level);
			EGLOG(Log, TEXT("Level Text %s"), *LevelText);
		}
		
		Txt_Level->SetText(FText::FromString(LevelText));
		});
	//==================================================
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
	CurrentPlayerInventory->OnItemUpdated.BindUObject(this,&UGameWidget::UpdateItemes);

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

void UGameWidget::BindCharacterTimeLimit(UComponent_TimeLimit* NewTimeLimit)
{
	CurrentPlayerTimeLimit = NewTimeLimit;

}

void UGameWidget::BindCharacterStamina(UComponent_Stamina* NewStamina)
{
	CurrentPlayerStamina = NewStamina;

	CurrentPlayerStamina->OnStaminaChanged.BindUObject(this, &UGameWidget::UpdateStamina);
	if (CurrentPlayerStamina->OnStaminaChanged.IsBound())
	{
	CurrentPlayerStamina->OnStaminaChanged.Execute();
	}

}


