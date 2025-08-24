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
		float sld_MasterValue=1.0f;
	UPROPERTY(BlueprintReadWrite)
		float sld_BGMValue=1.0f;
	UPROPERTY(BlueprintReadWrite)
		float sld_SEValue=1.0f;
	UPROPERTY(BlueprintReadWrite)
		float sld_VoiceValue=1.0f;
	UPROPERTY(BlueprintReadWrite)
		float sld_UIValue=1.0f;
	UPROPERTY(BlueprintReadWrite)
		FIntPoint ScreenResoultion=FIntPoint( 1920, 1080);
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> WindowMode = EWindowMode::Fullscreen;
		
	void SetValues(float sld_Master, float sld_BGM, float sld_SE, float sld_Voice, float sld_UI, FIntPoint ScreenResoultion, EWindowMode::Type WindowMode);


};
