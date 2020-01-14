// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGConerGenerator.h"


// Sets default values
APCGConerGenerator::APCGConerGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Path = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PATH"));
	Coner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CONER"));
	nConer = 5;
	Floor = 100;
	XRange = 10;


}

// Called when the game starts or when spawned
void APCGConerGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	
	ConerCoordinations.Init(FVector::ZeroVector, nConer);
	
	//UE_LOG(LogTemp, Error, TEXT("ASDFASDFSADFASDF"));
	GenerateConers();
}

// Called every frame
void APCGConerGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APCGConerGenerator::GenerateConers()
{
	for  (auto & var : ConerCoordinations)
	{
		//UE_LOG(LogTemp, Error, TEXT("!!!!!!!!!!!ASDFASDFSADF5848443ASDF"));
		var += generateCoord();
		auto obj= GetWorld()->SpawnActor(ATestSpawnActor::StaticClass() );
		obj->SetActorLocation(var);
		CreatedConers.Add(obj);
		obj->
	}

	//from now, we need a meter param. not 1cm param. so we multiply 100 for make it to meter.
	XRange *= 100;


}

FVector APCGConerGenerator::generateCoord()
{
	FVector result;
	 
	float x= FMath::RandRange(-XRange, XRange);
	x -= ((int32)x % 10);
	float y= FMath::RandRange(-XRange, XRange);
	y -= ((int32)x % 10);
	//UE_LOG(LogTemp, Warning, TEXT("x = %f , Y= %f"), x, y);
	 result.X = x*100;
	 result.Y = y*100;
	result.Z = Floor;


	return result;
}

