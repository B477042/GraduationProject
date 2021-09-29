// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Stamina.h"

UComponent_Stamina::UComponent_Stamina()
{

}
float UComponent_Stamina::GetStaminaRatio()
{
	return (Stamina < 0.0f) ? 0.0f : Stamina / MaxStamina; 
}

void UComponent_Stamina::TurnOnTickStamina()
{
	SetComponentTickEnabled(true);
}

void UComponent_Stamina::UseStaticStamina()
{
	if (!bCanUsingStamina)
	{
		EGLOG(Log, TEXT("Can't using Stamina"));
		return;
	}
	Stamina -= UsageOfStatic;
	if (Stamina <= 0.0f)
	{

	}

	OnStaminaChanged.Execute(GetStaminaRatio());

}

void UComponent_Stamina::BeginPlay()
{
	Super::BeginPlay();
}

void UComponent_Stamina::BeginDestroy()
{
	Super::BeginDestroy();
	if (OnStaminaChanged.IsBound())
	{
		OnStaminaChanged.Unbind();
	}
	
	 
}

void UComponent_Stamina::UsingTick(float DeltaTime)
{
	if (Stamina <= 0.0f)
	{
		bCanUsingStamina = false;

	}

	//Use Tick
	if (!bIsStaminaUsing|| !bCanUsingStamina)
	{

		return;
	}
	
	Stamina -= UsingFactor;
	
}

void UComponent_Stamina::RecoverTick(float DeltaTime)
{
	//Recover Tick
	if (GetStaminaRatio() < 1.0f)
	{
		Stamina += RecoverFactor;

	}
	else
	{
		Stamina = MaxStamina;
		SetComponentTickEnabled(false);
		bCanUsingStamina = true;
	}


}

void UComponent_Stamina::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	//Subtract Stamina as owner use
	UsingTick(DeltaTime);
	//Recover Stamina until Stamina value same as MaxStamina value
	RecoverTick(DeltaTime);
}
