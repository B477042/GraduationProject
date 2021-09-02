// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "BarrierEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UBarrierEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBarrierEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy()override;


public:	
	void ActivateEffect(const FVector& Pos);
	void DeactivateEffect();

	TSoftObjectPtr<class ABarrierEffectActor> EffectActor;
};
