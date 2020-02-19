// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_Player.h"

UStatComponent_Player::UStatComponent_Player()
{

}

void UStatComponent_Player::InitializeComponent()
{
	Super::InitializeComponent();
}

void UStatComponent_Player::BeginPlay()
{
	Super::BeginPlay();
}



void UStatComponent_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UStatComponent_Player::CheckCanComboAttack() const
{
	return bIsComboAttackInputOn;
}

bool UStatComponent_Player::CheckCanChargeAttack() const
{
	return bIsChargeAttackInputOn;
}

int32 UStatComponent_Player::GetMaxCombo() const
{
	return MaxCombo;
}

int32 UStatComponent_Player::GetCurrentCombo() const
{
	return CurrentCombo;
}
