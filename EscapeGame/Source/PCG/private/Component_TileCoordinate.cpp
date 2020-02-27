// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_TileCoordinate.h"

// Sets default values for this component's properties
UComponent_TileCoordinate::UComponent_TileCoordinate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	TileCoord = FVector::ZeroVector;
	// ...
}


// Called when the game starts
void UComponent_TileCoordinate::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComponent_TileCoordinate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UComponent_TileCoordinate::LoadTileSize(const FVector & Other)
{
	TileSize = Other;
}

const FVector UComponent_TileCoordinate::GetTileCoord()
{
	return TileCoord;
}

 FVector UComponent_TileCoordinate::ConvertWorldToTile(FVector  Other)
{


	return  TileSize / Other  ;
}

const FVector UComponent_TileCoordinate::ConvertTileToWorld()
{
	
	return  TileCoord * TileSize;
}



