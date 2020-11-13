// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_Enemy.h"
#include "EGSaveGame.h"

UStatComponent_Enemy::UStatComponent_Enemy()
{
	MinWalkingSpeed = 0.0f;
	MaxWalkingSpeed = 350.0f;
	MaxRunningSpeed = 700.0f;
	Type = 0;
}

void UStatComponent_Enemy::InitializeComponent()
{
	Super::InitializeComponent();
}

void UStatComponent_Enemy::BeginPlay()
{
	Super::BeginPlay();

}

void UStatComponent_Enemy::SaveGame(UEGSaveGame * SaveInstance)
{
}

void UStatComponent_Enemy::LoadGame(const UEGSaveGame * LoadInstance)
{
}

void UStatComponent_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UStatComponent_Enemy::GetDropExp()
{
	return DropExp;
}

void UStatComponent_Enemy::SetType(int32 input)
{
	Type = input;
}



