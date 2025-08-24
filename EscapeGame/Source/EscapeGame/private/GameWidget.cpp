// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameWidget.h"

#include "Actor/Item/Item_CardKey.h"
#include "Actor/Item/Item_Recover.h"
#include "Component/Component_TimeLimit.h"
#include "Component/StatComponent_Player.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Components/Image.h"
#include "GameAbility/Component_Fury.h"
#include "GameAbility/Component_Inventory.h"
#include "GameAbility/Component_Stamina.h"
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
	Img_Fury = Cast<UImage>(GetWidgetFromName(TEXT("FuryImage")));
	
	DisplayTime = 0.0f;
	
	
	PlayerHP = 100.0f;
	//PlayerStamina = 100.0f;
	HPAmount = 0;
	FuryBarColor1 = FLinearColor::Black;
	FuryBarColor2 = FLinearColor::Red;
 

	EGLOG(Error, TEXT("Widget Native Constructor"));

	

}

void UGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}


//������ character�� stat component���� ä���� �ٲ� ��, ȣ��ȴ�. 
void UGameWidget::UpdateCharacterStat()
{
	if (CurrentPlayerStat.IsValid())
	{
		
		PlayerHP=CurrentPlayerStat->GetHP();
		float PlayerHPRatio = CurrentPlayerStat->GetHPRatio()*100.0f;
		float BlurRate = 0.5f*(1.0f - CurrentPlayerStat->GetHPRatio());


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
	//Card Key Item ó��
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
	//Recover Item ó��
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

		Img_Fury->SetOpacity(1.0f);
		return;
	}

	FLinearColor NewColor = FLinearColor::LerpUsingHSV(FuryBarColor1, FuryBarColor2, Ratio);
	PB_Fury->SetFillColorAndOpacity(NewColor );
	Img_Fury->SetOpacity(0.0f);

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




//Tickó�� �����Ǵ� �� Ȯ��
//BP�� ���ε� �� �Լ��� ��� ���� ��
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

void UGameWidget::BindCharacterInventory(UComponent_Inventory * newInven)
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
	//�κ��丮�� ��������Ʈ�� ���� ����
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
	CurrentPlayerFury->OnFuryChanged.BindUObject(this,&UGameWidget::UpdateFury );

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


