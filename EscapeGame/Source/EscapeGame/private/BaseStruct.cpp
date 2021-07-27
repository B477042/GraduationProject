// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStruct.h"
#include "Materials/MaterialInstance.h"
#include "Components/BoxComponent.h"
#include "EGPlayerCharacter.h"
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
	

	
	/*
	 * =====================================================
	 * Trigger Setting
	 */
	TileTrigger->SetCollisionProfileName(TEXT("OnTrapTrigger"));
}

// Called when the game starts or when spawned
void ABaseStruct::BeginPlay()
{
	Super::BeginPlay();
	/*
	 *======================================================
	 * Material Parameters
	 */
	auto TileMaterial = UMaterialInstanceDynamic::Create(MiniMapTileMesh->GetMaterial(0), MiniMapTileMesh->GetMaterial(0));
	
	
	if (!TileMaterial)
	{
		EGLOG(Error, TEXT("TileMaterial is null"));
		return;
	}
	FMaterialParameterInfo MaterialParameterInfo;
	MaterialParameterInfo.Name = Name_MainColor;
	MaterialParameterInfo.Association = EMaterialParameterAssociation::GlobalParameter;
	MaterialParameterInfo.Index = INDEX_NONE;
	
	
	//Set Dynamic Color
	bool bResult = TileMaterial->GetVectorParameterValue(MaterialParameterInfo, Color_Default);
	if (!bResult)
	{
		EGLOG(Warning, TEXT("Get Vector Failed"));
	}
	Color_OnPlayer = FLinearColor(255, 255, 255, 1);
}

void ABaseStruct::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TileTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseStruct::OnComponenetBeginOverlap);
	TileTrigger->OnComponentEndOverlap.AddDynamic(this, &ABaseStruct::OnComponentEndOverlap);
}

void ABaseStruct::OnComponenetBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	EGLOG(Warning, TEXT("Entered"));

}

void ABaseStruct::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EGLOG(Warning, TEXT("Exit"));


}

// Called every frame
void ABaseStruct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

