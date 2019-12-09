// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "SpearActor.generated.h"

UCLASS()
class ESCAPEGAME_API ASpearActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpearActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;
	//point to tail of Spear
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Root;
	UPROPERTY(EditInstanceOnly, Category = Stat)
		float Durability;
};
