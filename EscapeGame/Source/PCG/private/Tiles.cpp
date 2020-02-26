// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles.h"

// Sets default values
ATiles::ATiles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}
	RootComponent = BoxCollision;
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATiles::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

