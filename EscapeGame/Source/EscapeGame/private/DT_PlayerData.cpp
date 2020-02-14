// Fill out your copyright notice in the Description page of Project Settings.


#include "DT_PlayerData.h"

// Sets default values
ADT_PlayerData::ADT_PlayerData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADT_PlayerData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADT_PlayerData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

