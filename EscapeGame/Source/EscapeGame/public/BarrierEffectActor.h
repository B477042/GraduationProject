// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "BarrierEffectActor.generated.h"

UCLASS()
class ESCAPEGAME_API ABarrierEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrierEffectActor();

	void ActivateEffect();
	void DeactivateEffect();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	


	UPROPERTY(VisibleAnywhere, Category = "Barrier")
		UStaticMeshComponent* EnergySphere;
	UPROPERTY(VisibleAnywhere, Category = "Barrier")
		UStaticMeshComponent* WaveSphere;

};
