// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStruct.h"
#include "Materials/MaterialInstance.h"
#include "Components/BoxComponent.h"
#include "EGPlayerCharacter.h"
#include "MiniMapTileManager.h"


bool ABaseStruct::bIsPlayerCaptured = false;

// Sets default values
ABaseStruct::ABaseStruct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SCENEROOT"));
	MiniMapTileMesh = CreateDefaultSubobject<UMiniMapMarkerComponent>(TEXT("MINIMAPTILEMESH"));
	TileTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TileTrigger"));

	/*
	 *=====================================================
	 * Components Tree
	 */
	RootComponent = SceneRoot;
	SceneRoot->SetMobility(EComponentMobility::Static);
	MiniMapTileMesh->SetupAttachment(SceneRoot);
	TileTrigger->SetupAttachment(SceneRoot);
	/*
	 * ======================================================
	 * Material asset
	 */
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_Marker(TEXT("MaterialInstanceConstant'/Game/MyFolder/My_Material/MaterialInstance/MI_PathMarker.MI_PathMarker'"));
	if(MI_Marker.Succeeded())
	{
		//TileMaterial = UMaterialInstanceDynamic::Create(MI_Marker.Object, MI_Marker.Object);
		MiniMapTileMesh->SetMaterial(0, MI_Marker.Object);
		
	}
	else
	{
		EGLOG(Error, TEXT("Material load failed"));
	}
	
	MiniMapTileMesh->SetRelativeLocation(POS_Minimap);
	MiniMapTileMesh->SetMobility(EComponentMobility::Stationary);
	MiniMapTileMesh->SetRelativeLocation(POS_Minimap);

	
	Color_OnPlayer = FLinearColor(255, 255, 255, 1);

	
	/*
	 * =====================================================
	 * Trigger Setting
	 */
	TileTrigger->SetCollisionProfileName(TEXT("OnTrapTrigger"));
}

void ABaseStruct::SetTileOpacity(const float NewValue)
{
	if (!MID_Tile)
	{
		UE_LOG(LogTemp, Log, TEXT("MID Tile is nullptr"));
		return;
	}
	MID_Tile->SetScalarParameterValue(Name_Opacity, NewValue);

}

// Called when the game starts or when spawned
void ABaseStruct::BeginPlay()
{
	Super::BeginPlay();
	/*
	 *======================================================
	 * Material Parameters
	 */
	MID_Tile = MiniMapTileMesh->CreateDynamicMaterialInstance(0);
	if(!MID_Tile)
	{
		EGLOG(Error, TEXT("Failed to Create MID"));
		return;
	}

	
	
	 const bool bResult = MID_Tile->GetVectorParameterValue(Name_MainColor,
		 Color_Default);
	if(!bResult)
	{
		EGLOG(Error, TEXT("Failed to get Color Param"));
		return;
	}
	
	if (bIsPlayerCaptured)
	{
		bIsPlayerCaptured = false;
	}
}

void ABaseStruct::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TileTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseStruct::OnComponentBeginOverlap);
	TileTrigger->OnComponentEndOverlap.AddDynamic(this, &ABaseStruct::OnComponentEndOverlap);
}

void ABaseStruct::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	//Check Is Player

	auto Player = Cast<AEGPlayerCharacter>(OtherActor);
	if(!Player)
	{
		return;
	}
	//Change Tile Color 
	MID_Tile->SetVectorParameterValue(Name_MainColor, Color_OnPlayer);

	

	//If 'bIsPlayerCaputred' is ture, return function
	if (bIsPlayerCaptured)
	{
		return;
	}
	
	//Set 'bIsPlayerCaptured' to true
	bIsPlayerCaptured = true;
	//Run Multi-Thread 

	const auto World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Log, TEXT("World Invailed!"));
		return;
	}

	TArray<AActor*>Results;

	UGameplayStatics::GetAllActorsOfClass(World, AMiniMapTileManager::StaticClass(), Results);
	//Cast AActor=================>MiniMapTileManager
	if (Results.Num() == 0)
	{
		EGLOG(Error, TEXT("Results is empty"));
		return;
	}

	const auto Manager = Cast<AMiniMapTileManager>(Results[0]);
	if (!Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("Casting Failed"));
	}
	EGLOG(Error, TEXT("Runn"));
	//Run Thread 
	(new FAutoDeleteAsyncTask<CalcMiniMapTileAsyncTask>(Manager, Player))->StartBackgroundTask();

	
}

void ABaseStruct::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	auto Player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!Player)
	{
		return;
	}
	MID_Tile->SetVectorParameterValue(Name_MainColor, Color_Default);
	
}

// Called every frame
void ABaseStruct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

