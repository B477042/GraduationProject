// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrierEffectComponent.h"
#include "BarrierEffectActor.h"

// Sets default values for this component's properties
UBarrierEffectComponent::UBarrierEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBarrierEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UWorld* World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is invalid"));
		return;
	}

	EffectActor = World->SpawnActor<ABarrierEffectActor>();
}

void UBarrierEffectComponent::BeginDestroy()
{
	Super::BeginDestroy();
	/*if (EffectActor.IsValid())
	{
		EGLOG(Log, TEXT("Delete Effect Actor"));
		EffectActor->Destroy();
	}*/
	//EGLOG(Log, TEXT("Component Destory"));
	
}

void UBarrierEffectComponent::ActivateEffect(const FVector& Pos)
{
	EffectActor->SetActorLocation(Pos);
	EffectActor->ActivateEffect();
}

void UBarrierEffectComponent::DeactivateEffect()
{
	EffectActor->DeactivateEffect();
}



