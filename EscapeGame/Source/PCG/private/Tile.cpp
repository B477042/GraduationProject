// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//TileSystem = CreateDefaultSubobject<UComponent_TileCoordinate>(TEXT("TileSystem"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}

	RootComponent = BoxCollision;
	Mesh->SetupAttachment(RootComponent);
	TailRadius = FVector(50.0f, 50.0f, 50.0f)*2.0f;
	BoxCollision->SetBoxExtent(TailRadius/2.0f);
	//TileSystem->LoadTileSize(BoxSize);

	
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	PCGCoord = new FPCGCoord(GetActorLocation(), TailRadius);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ATile::GetTailRadius()
{
	return TailRadius;
}

