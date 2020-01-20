// Fill out your copyright notice in the Description page of Project Settings.


#include "GruntCharacter.h"


AGruntCharacter::AGruntCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGruntCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGruntCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGruntCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
