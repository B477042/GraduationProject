// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStruct.h"
#include "Materials/MaterialInstanceDynamic.h"
// Sets default values
ABaseStruct::ABaseStruct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SCENEROOT"));
	MiniMapTileMesh = CreateDefaultSubobject<UMiniMapMarkerComponent>(TEXT("MINIMAPTILEMESH"));

	RootComponent = SceneRoot;
	SceneRoot->SetMobility(EComponentMobility::Static);
	MiniMapTileMesh->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_Marker(TEXT("MaterialInstanceConstant'/Game/MyFolder/My_Material/MaterialInstance/MI_PathMarker.MI_PathMarker'"));
	if(MI_Marker.Succeeded())
	{
		TileMaterial = UMaterialInstanceDynamic::Create(MI_Marker.Object, MI_Marker.Object);
		MiniMapTileMesh->SetMaterial(0, TileMaterial);
		
	}
	
	MiniMapTileMesh->SetRelativeLocation(POS_Minimap);
	MiniMapTileMesh->SetMobility(EComponentMobility::Static);
	MiniMapTileMesh->SetRelativeLocation(POS_Minimap);
	

	/*
	 *======================================================
	 * Material Parameters
	 */
	FMaterialParameterInfo MaterialParameterInfo;
	MaterialParameterInfo.Name = Name_MainColor;
	//Set Dynamic Color
	bool bResult = TileMaterial->GetVectorParameterValue(MaterialParameterInfo, Color_Default);
	if(!bResult)
	{
		EGLOG(Warning, TEXT("Get Vector Failed"));
	}
	Color_OnPlayer = FLinearColor(255, 255, 255, 1);
	
}

// Called when the game starts or when spawned
void ABaseStruct::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseStruct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

