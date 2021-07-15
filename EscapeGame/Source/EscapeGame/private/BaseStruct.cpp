// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStruct.h"

// Sets default values
ABaseStruct::ABaseStruct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SCENEROOT"));
	MiniMapTileMesh = CreateDefaultSubobject<UMiniMapMarkerComponent>(TEXT("MINIMAPTILEMESH"));

	RootComponent = SceneRoot;
	SceneRoot->SetMobility(EComponentMobility::Stationary);
	MiniMapTileMesh->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_Marker(TEXT("MaterialInstanceConstant'/Game/MyFolder/My_Material/MaterialInstance/MI_PathMarker.MI_PathMarker'"));
	if(MI_Marker.Succeeded())
	{
		MiniMapTileMesh->SetMaterial(0, MI_Marker.Object);
	}
	
	MiniMapTileMesh->SetRelativeLocation(POS_Minimap);
	MiniMapTileMesh->SetMobility(EComponentMobility::Stationary);
	MiniMapTileMesh->SetRelativeLocation(POS_Minimap);
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

