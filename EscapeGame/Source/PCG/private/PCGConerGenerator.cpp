// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGConerGenerator.h"
#include "TestSpawnActor.h"

// Sets default values
APCGConerGenerator::APCGConerGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Path = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PATH"));
	Coner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CONER"));
	nConer = 5;
	Floor = 100;
	XRange = 100;


}

// Called when the game starts or when spawned
void APCGConerGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	
	ConerCoordinations.Init(FVector::ZeroVector, nConer);
	
	UE_LOG(LogTemp, Error, TEXT("ASDFASDFSADFASDF"));
	GenerateConers();
}

// Called every frame
void APCGConerGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APCGConerGenerator::GenerateConers()
{
	for  (auto var : ConerCoordinations)
	{
		UE_LOG(LogTemp, Error, TEXT("!!!!!!!!!!!ASDFASDFSADF5848443ASDF"));
		var += generateCoord();
		auto obj= GetWorld()->SpawnActor(ATestSpawnActor::StaticClass() );
		obj->SetActorLocation(var);
	}

}

FVector APCGConerGenerator::generateCoord()
{
	FVector result;
	result.X=  FMath::RandRange(-XRange, XRange);
	result.Y = FMath::RandRange(-XRange, XRange);
	result.Z = Floor;


	return result;
}

