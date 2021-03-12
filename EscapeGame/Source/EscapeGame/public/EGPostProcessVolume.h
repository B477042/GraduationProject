// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "EGPostProcessVolume.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AEGPostProcessVolume : public APostProcessVolume
{
	GENERATED_BODY()
public:
	AEGPostProcessVolume();

	//StatComponent_Player에서 호출 됨. player의 hp 비율을 받아서 비율에 따라 포스트 프로세스 이펙트가 적용되게 한다. 100%라면 피격효과가 없고
	//0이라면 피격효과가 최대가 되게 한다
	void SyncHpPercent(float ratio);
protected:
	virtual void PostInitializeComponents()override;
	virtual void BeginPlay()override;

	void SaveGame(class UEGSaveGame* SaveInstance);
	void LoadGame(const class UEGSaveGame* LoadInstance);

	

private:


	const FVector4 DefaultColorGamma = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
	const FVector4 DefaultColorContrast = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
	const FVector4 DefaultColorSaturation = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
	const float DefaultGrainJitter=0.0f;
	const float DefaultGrainIntensity=0.0f;
	const float DefaultVignettelIntensity=0.4f;


	const FVector4 MaxColorGamma = FVector4(1.0f, 1.0f, 1.0f, 0.0f);
	const FVector4 MaxColorContrast = FVector4( 1.000000f,  1.000000f,  1.000000f, 1.460000f);
	const FVector4 MaxColorSaturation = FVector4(1.0f,  1.0f,  1.00f,  0.000000f);
	const float MaxGrainJitter=1.0f;
	const float MaxGrainIntensity=0.4f;
	const float MaxVignetteIntensity= 0.523810f;

};
