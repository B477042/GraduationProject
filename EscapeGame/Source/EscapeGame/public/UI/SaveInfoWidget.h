// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SaveInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API USaveInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativePreConstruct()override;

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
		bool LoadSaveData();

protected:
	UPROPERTY()
		 UTextBlock* Txt_PlayerLevel;
	UPROPERTY()
		UTextBlock* Txt_PlayerFury;
	UPROPERTY()
		 UTextBlock* Txt_PlayerHP;
	UPROPERTY()
		 UTextBlock* Txt_Remaintime;
	UPROPERTY()
		UTextBlock* Txt_StageName;
	UPROPERTY()
		UTextBlock* Txt_FileName;

	UPROPERTY(BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = true, ExposeOnSpawn = true))
		FName ToLoadData;
};
