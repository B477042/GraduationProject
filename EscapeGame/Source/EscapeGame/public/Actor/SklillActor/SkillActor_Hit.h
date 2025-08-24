// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillActor.h"
#include "SkillActor_Hit.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API ASkillActor_Hit : public ASkillActor
{
	GENERATED_BODY()
public:
	ASkillActor_Hit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void UseSkill(const FVector& Point);
protected:
	UFUNCTION()
	void OnSystemEnd(UParticleSystemComponent *PS);

};
