// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_Enemy.h"


UStatComponent_Enemy::UStatComponent_Enemy()
{
	MinWalkingSpeed = 0.0f;
	MaxWalkingSpeed = 350.0f;
	MaxRunningSpeed = 700.0f;
}

void UStatComponent_Enemy::InitializeComponent()
{
	Super::InitializeComponent();
}

void UStatComponent_Enemy::BeginPlay()
{
	Super::BeginPlay();

}

void UStatComponent_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UStatComponent_Enemy::GetDropExp()
{
	return DropExp;
}

