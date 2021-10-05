// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "SkillActor.h"
#include "SkillActor_PlayerFury.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API ASkillActor_PlayerFury : public ASkillActor
{
	GENERATED_BODY()
public:
	ASkillActor_PlayerFury();
	void UseSkill(const FVector& Point);
protected:
	virtual void PostInitializeComponents()override;
	UFUNCTION()
		void OnSystemEnd(UParticleSystemComponent* PS);
};
