// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionSaveGame.h"

void UOptionSaveGame::SetValues(float sld_Master, float sld_BGM, float sld_SE, float sld_Voice, float sld_UI, FIntPoint ScreenResoultion, EWindowMode::Type WindowMode)
{
	sld_MasterValue = sld_Master;
	sld_BGMValue = sld_BGM;
	sld_SEValue = sld_SE;
	sld_VoiceValue = sld_Voice;
	sld_UIValue = sld_UI;

	this->ScreenResoultion = ScreenResoultion;
	this->WindowMode = WindowMode;
}
