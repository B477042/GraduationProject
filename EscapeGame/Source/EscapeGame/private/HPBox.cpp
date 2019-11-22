// Fill out your copyright notice in the Description page of Project Settings.

#include "HPBox.h"

// Sets default values
AHPBox::AHPBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHPBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHPBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void AHPBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

