// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Stamina.h"

UComponent_Stamina::UComponent_Stamina()
{
	bCanUsingStamina = true;
	bIsStaminaUsing = false;
	
}
bool UComponent_Stamina::CanUseStamina()
{
	return  bCanUsingStamina;
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
		Stamina = 0.0f;
	}



}

void UComponent_Stamina::SetUsingStamina(bool bResult)
{
	bIsStaminaUsing = bResult;
}

void UComponent_Stamina::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
}

void UComponent_Stamina::BeginDestroy()
{
	Super::BeginDestroy();
	
	 
}

void UComponent_Stamina::UsingTick()
{
	if (Stamina <= 0.0f)
	{
		bCanUsingStamina = false;
		bIsStaminaUsing = false;
	}


	if (!bIsStaminaUsing)
	{
		return;
	}
	if (!bCanUsingStamina)
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
	UsingTick();
	//Recover Stamina until Stamina value same as MaxStamina value
	RecoverTick(DeltaTime);
	if (OnStaminaChanged.IsBound())
	{
		OnStaminaChanged.Execute();
	}
}
