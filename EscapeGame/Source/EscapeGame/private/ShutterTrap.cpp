// Fill out your copyright notice in the Description page of Project Settings.

#include "ShutterTrap.h"

// Sets default values
AShutterTrap::AShutterTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShutterTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShutterTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShutterTrap::initComponents()
{
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ROOT"));
	SoundEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("SE"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

}

