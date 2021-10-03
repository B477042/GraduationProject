// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Image.h"
#include "StatComponent_Player.h"
#include "Math/Color.h"
#include "GameWidget.generated.h"

/**
 * HUD System Class
 * Main UI for Player
 * Display Timer and MiniMap, HP
 */

//DECLARE_DELEGATE_OneParam(FBindStat,UCharacterStatComponent);



UCLASS()
class ESCAPEGAME_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UGameWidget();
	//void BindCharacterStat(class UGameStat* NewCharacterStat);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct()override;
	
	void BindCharacterStat( UStatComponent_Player* newStat);
	void BindCharacterInven(class UComponent_Inventory* newInven);
	void BindCharacterFury(class UComponent_Fury* newFury);
	void BindCharacterTimeLimit(class UComponent_TimeLimit* NewTimeLimit);
	void BindCharacterStamina(class UComponent_Stamina* NewStamina);
	
	//FBindStat BindStatDelegate;
	//Update UI's Hp
	UFUNCTION(BlueprintCallable)
		void UpdateCharacterStat();
	//Update UI's Stamina
		void UpdateStamina();
	//Update Item's Info. Call by Delegate in inventory Comp
	UFUNCTION(BlueprintCallable)
	void UpdateItemes(FName ItemName, int Amount);
	UFUNCTION(BlueprintCallable)
		void UpdateFury(float Ratio);
	
		void UpdateExp();

	UFUNCTION(BlueprintCallable)
		FText BindingTimeText();
	UFUNCTION(BlueprintCallable)
		FLinearColor BindingTimeColor();

	
 
	

 

protected:

	virtual void NativeOnInitialized() override;



	UPROPERTY(BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UStatComponent_Player>CurrentPlayerStat;
	UPROPERTY(BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UComponent_Inventory>CurrentPlayerInventory;
	UPROPERTY(BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UComponent_Fury>CurrentPlayerFury;
	UPROPERTY(BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UComponent_TimeLimit>CurrentPlayerTimeLimit;
	UPROPERTY(BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UComponent_Stamina>CurrentPlayerStamina;

	UPROPERTY(BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class ACharacter>OwnerChara;

	
	UPROPERTY()
	class UProgressBar* PB_Stamina;
	UPROPERTY()
	class UProgressBar* PB_Fury;
	UPROPERTY()
		class UProgressBar* PB_Exp;
	//Image Box of Player's Hp
	UPROPERTY()
	UImage* Img_Battery;
	UPROPERTY()
	UImage* Img_Cardkey;
	//Display Player's HP Statue as Image. Set images on BP
	UPROPERTY(BlueprintReadWrite, Category = "Images", meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> Imgs_Battary;
	UPROPERTY(BlueprintReadWrite, Category = "Images", meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> Img_Cardkeys;
	UPROPERTY()
		class UTextBlock* Txt_CardKey;
	//Image of Itme Recovery Item
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* Img_RecoveryItem;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* Txt_TimerBlock;
	
	/*
	*
	*/
	UPROPERTY()
		class UTextBlock* Txt_Level;
	UPROPERTY()
		class UTextBlock* RecoveryItemNum;//Write 'HP'
	UPROPERTY(BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int HPAmount;
	//
	
	UPROPERTY(BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float PlayerHP;
	//UPROPERTY(BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	//	float PlayerStamina;
	
	float DisplayTime;

	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	int N_RecoveryItems=0;
	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	int N_CardKeyItems=0;
	
	UPROPERTY(BlueprintReadWrite, Category = "Fury", meta = (AllowPrivateAccess = true))
		FLinearColor FuryBarColor1;

	UPROPERTY(BlueprintReadWrite, Category = "Fury", meta = (AllowPrivateAccess = true))
		FLinearColor FuryBarColor2;
	//Inventory UI Data Variables
	//UPROPERTY(VisibleAnywhere, Category = "GamState")
	TWeakObjectPtr<class AEGGameState>GameState;
	 
};
