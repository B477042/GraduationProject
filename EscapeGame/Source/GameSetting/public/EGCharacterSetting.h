// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EGCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(Config=GameSetting,Blueprintable,BlueprintType)
class GAMESETTING_API UEGCharacterSetting : public UObject
{
	GENERATED_BODY()
public:
	UEGCharacterSetting();
	UPROPERTY(Config)
		TArray<FSoftObjectPath>CharacterAssets;
	UPROPERTY(Config)
		TArray<FSoftObjectPath>TargetTexture;
	UPROPERTY(Config)
		TArray<FSoftObjectPath>AnimBlueprints;
//private:
	
};
