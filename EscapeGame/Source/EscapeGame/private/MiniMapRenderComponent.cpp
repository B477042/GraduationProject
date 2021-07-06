// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniMapRenderComponent.h"
#include"Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialInstance.h"
#include"GameSetting/public/EGCharacterSetting.h"

// Sets default values for this component's properties
UMiniMapRenderComponent::UMiniMapRenderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//TextureRenderTarget2D'/Game/MyFolder/MiniMap/MiniMapRender.MiniMapRender'
	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D>T_TextureTarget(TEXT("/Game/MyFolder/MiniMap/MiniMapRender.MiniMapRender"));
	if (T_TextureTarget.Succeeded())
	{
		this->TextureTarget = Cast<UTextureRenderTarget2D>(T_TextureTarget.Object);

	}
	ProjectionType = ECameraProjectionMode::Orthographic;
	
	this->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	bCaptureEveryFrame = true;
	//TextureTarget->AdjustBrightness = 255.0f;

	//Don't Caputre Skeletal Meshes
	ShowFlags.SkeletalMeshes = false;
	ShowFlags.EyeAdaptation = false;
 
	//미니맵 용 포스트 프로세스 인스턴스 불러오기 및 포스트 프로세스 설정
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_Post(TEXT("MaterialInstanceConstant'/Game/MyFolder/MiniMap/MI_Minimap_OutLine.MI_Minimap_OutLine'"));
	if(MI_Post.Succeeded())
	{
		FWeightedBlendable Weighted;
		Weighted.Object = Cast<UMaterialInstance>(MI_Post.Object);
		Weighted.Weight = 1;
		PostProcessSettings.WeightedBlendables.Array.Add(Weighted);
		
	}
}


// Called when the game starts
void UMiniMapRenderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMiniMapRenderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

