// Fill out your copyright notice in the Description page of Project Settings.


#include "EGPostProcessVolume.h"
#include "EGGameInstance.h"
#include "EGSaveGame.h"


AEGPostProcessVolume::AEGPostProcessVolume()
{
	//Extend Bound Infinity
	bUnbound = true;
	
	//enable Process Effect
	Settings.bOverride_ColorGamma = true;
	Settings.bOverride_ColorContrast = true;
	Settings.bOverride_ColorSaturation = true;
	Settings.bOverride_GrainIntensity = true;
	Settings.bOverride_GrainJitter = true;
	Settings.bOverride_VignetteIntensity = true;
	Settings.bOverride_BloomIntensity = true;
	Settings.bOverride_ScreenSpaceReflectionMaxRoughness = true;
	Settings.bOverride_ScreenSpaceReflectionIntensity = true;
	

	//
	
	
	//Bloom Intensity
	Settings.BloomIntensity = 1.961905f;
	
	//auto exposure
	Settings.AutoExposureBias = 1.5f;

	//scrren space reflections
	Settings.ScreenSpaceReflectionQuality = 80.952385f;
	Settings.ScreenSpaceReflectionMaxRoughness = 0.613429f;

	//Post Process Matrial 로드. 
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_Post(TEXT("MaterialInstanceConstant'/Game/MyFolder/My_Material/MaterialInstance/MI_OutLineShader.MI_OutLineShader'"));
	if (MI_Post.Succeeded())
	{
		FWeightedBlendable Weighted;
		Weighted.Object = Cast<UMaterialInstance>(MI_Post.Object);
		Weighted.Weight = 1;
		
		Settings.WeightedBlendables.Array.Add(Weighted);

	}
	

}

void AEGPostProcessVolume::SyncHpPercent(float ratio)
{
	/*	식
	*	적용값 = 최대적용값*(1.0f - ratio)
	*	채력이 최대라면 | 적용값 = 0
	*	채력이 0이라면 | 적용값 = 최대적용값 * (1.0-0) = 최대적용값
	*/

	float applyRatio = 1.0f - ratio;

	Settings.ColorGamma.W = FMath::Lerp<float, float>(DefaultColorGamma.W,MaxColorGamma.W,applyRatio);
	Settings.ColorContrast.W = FMath::Lerp<float, float>(DefaultColorContrast.W, MaxColorContrast.W, applyRatio);
	Settings.ColorSaturation.W = FMath::Lerp<float, float>(DefaultColorSaturation.W, MaxColorSaturation.W, applyRatio);
	Settings.GrainJitter = FMath::Lerp<float, float>(DefaultGrainJitter, MaxGrainJitter, applyRatio);
	Settings.GrainIntensity = FMath::Lerp<float, float>(DefaultGrainIntensity, MaxGrainIntensity, applyRatio);
	Settings.VignetteIntensity = FMath::Lerp<float, float>(DefaultVignettelIntensity, MaxVignetteIntensity, applyRatio);


}

void AEGPostProcessVolume::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (!GetWorld())return;

	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)return;

	GameInstance->SetPostProcessVolume(this);
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AEGPostProcessVolume::SaveGame);
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AEGPostProcessVolume::LoadGame);
}

void AEGPostProcessVolume::BeginPlay()
{
	Super::BeginPlay();


}

void AEGPostProcessVolume::SaveGame(UEGSaveGame* SaveInstance)
{
	if (!SaveInstance)return;
	FPostProcessData data ;
	
	data.ColorContrastValue = Settings.ColorContrast;
	data.ColorGammaValue = Settings.ColorGamma;
	data.ColorSaturation = Settings.ColorSaturation;
	data.GrainJitter= Settings.GrainJitter;
	data.GrainIntensity= Settings.GrainIntensity;
	SaveInstance->PostProcessData = data;

}
void AEGPostProcessVolume::LoadGame(const UEGSaveGame* LoadInstance)
{
	if (!LoadInstance)return;
	const FPostProcessData data = LoadInstance->PostProcessData;

	Settings.ColorContrast= data.ColorContrastValue ;
	Settings.ColorGamma = data.ColorGammaValue;
	Settings.ColorSaturation = data.ColorSaturation;
	Settings.GrainJitter = data.GrainJitter;
	Settings.GrainIntensity = data.GrainIntensity;

}