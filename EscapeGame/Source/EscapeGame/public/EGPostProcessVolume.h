// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Engine/PostProcessVolume.h"
#include "EGPostProcessVolume.generated.h"

/**
 * https://docs.unrealengine.com/en-US/API/Runtime/Engine/Engine/APostProcessVolume/index.html
 */
UCLASS()
class ESCAPEGAME_API AEGPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()
public:
	
	AEGPostProcessVolume();
};
