// Fill out your copyright notice in the Description page of Project Settings.


#include "StateComponent.h"

// Sets default values for this component's properties
UStateComponent::UStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


bool UStateComponent::IsAttacking() const
{
	return false;
}

void UStateComponent::SetDontMove()
{
}

void UStateComponent::SetRunning()
{
}

void UStateComponent::SetWalking()
{
}

bool UStateComponent::IsDead()
{
	return false;
}

// Called when the game starts
void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

