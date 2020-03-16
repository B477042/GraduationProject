// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"


FVector ATile::TileRadius = FVector(100.0f, 100.0f, 100.0f)/2.0f;


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//TileSystem = CreateDefaultSubobject<UComponent_TileCoordinate>(TEXT("TileSystem"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}
	static ConstructorHelpers::FObjectFinder < UMaterial >M_MATERIAL(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));
	if (M_MATERIAL.Succeeded())
	{
		
		Mesh->SetMaterial(0,M_MATERIAL.Object);
	}


	RootComponent = BoxCollision;
	Mesh->SetupAttachment(RootComponent);
	
	BoxCollision->SetBoxExtent(TileRadius);
	//TileSystem->LoadTileSize(BoxSize);

	
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(GetActorLocation()/(TileRadius*2)*(TileRadius*2));
	PCGCoord.SetDefaultValue(GetActorLocation(), TileRadius);
	//UE_LOG(LogTemp, Warning, TEXT("ActorLocation : %s"), *GetActorLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("PCGLocation : %s"), *PCGCoord.GetPCGCoord().ToString());
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ATile::GetTileRadius()
{
	return TileRadius;
}

