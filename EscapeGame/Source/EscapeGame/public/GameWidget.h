// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/Image.h"
#include "StatComponent_Player.h"
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
	void TimeExtend(float addTime);
	void BindCharacterStat( UStatComponent_Player* newStat);
	void BindCharacterInven(class UComponent_Inventory* newInven);
	float GetGameTimer();
	//FBindStat BindStatDelegate;
	//Update UI's Hp
	UFUNCTION(BlueprintCallable)
		void UpdateCharacterStat();
	//Update UI's Stamina
	UFUNCTION(BlueprintCallable)
		void UpdateStamina();
	//Update Item's Info. Call by Delegate in inventory Comp
	UFUNCTION(BlueprintCallable)
	void UpdateItemes(FName ItemName, int Amount);
	
	UFUNCTION(BlueprintCallable)
		float CheackTimeOut(float NewValue);

	UPROPERTY(BlueprintReadWrite, Category = Timer, Meta = (AllowPrivateAccess = true))
		float RemainTime;
	
	void LoadGame(float Time) { GameTimer = Time; }

private:
	void loadImages();

private:
	UPROPERTY(BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UStatComponent_Player>CurrentCharacterStat;
	UPROPERTY(BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UComponent_Inventory>CurrentPlayerInventory;

	UPROPERTY(BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class ACharacter>OwnerChara;

	
	UPROPERTY()
	class UProgressBar* PB_Stamina;
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
	//Image of Itme Recovery Item
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* Img_RecoveryItem;


	UPROPERTY()
	UImage* Img_Blood;
	 

	UPROPERTY()
		class UTextBlock* RecoveryItemNum;//Write 'HP'
	UPROPERTY(BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int HPAmount;
	//
	
	UPROPERTY(BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float PlayerHP;
	UPROPERTY(BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float PlayerStamina;
	
	UPROPERTY(BlueprintReadWrite, Category = Timer, Meta = (AllowPrivateAccess = true))
		float GameTimer;
	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	int N_RecoveryItems=0;
	UPROPERTY(BlueprintReadOnly, Category = Inventory, Meta = (AllowPrivateAccess = true))
	int N_CardKeyItems=0;
	

	//Inventory UI Data Variables


	
};
