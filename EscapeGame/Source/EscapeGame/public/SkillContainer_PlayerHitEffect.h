// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component_SkillContainer.h"
#include "SkillActor_Hit.h"
#include "SkillContainer_PlayerHitEffect.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API USkillContainer_PlayerHitEffect : public UComponent_SkillContainer
{
	GENERATED_BODY()
public:
	USkillContainer_PlayerHitEffect();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void UseSkill(const AActor& TargetActor, const FVector& Direction, int n_Count = 1)override;
	void ActivateEffectAt(const FVector& At, int n_Count = 1);
	
};
