// Fill out your copyright notice in the Description page of Project Settings.

#include "Path1.h"

// Sets default values
APath1::APath1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BaseOfPath = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BASEOFPATH"));
	Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CEILING"));
	LeftSideWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEFTSIDEWALL"));
	RightSideWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIGHTSIDEWALL"));
	BodyOfLight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODYOFLIGHT"));

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("POINTLIGHT"));

	
	

}

// Called when the game starts or when spawned
void APath1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APath1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

