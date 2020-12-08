// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/SaveGame.h"
#include "OptionSaveGame.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ESCAPEGAME_API UOptionSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		float sld_MasterValue;
	UPROPERTY(BlueprintReadWrite)
		float sld_BGMValue;
	UPROPERTY(BlueprintReadWrite)
		float sld_SEValue;
	UPROPERTY(BlueprintReadWrite)
		float sld_VoiceValue;
	UPROPERTY(BlueprintReadWrite)
		float sld_UIValue;
	UPROPERTY(BlueprintReadWrite)
		FIntPoint ScreenResoultion;
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> WindowMode;
		
	void SetValues(float sld_Master, float sld_BGM, float sld_SE, float sld_Voice, float sld_UI, FIntPoint ScreenResoultion, EWindowMode::Type WindowMode);


};
