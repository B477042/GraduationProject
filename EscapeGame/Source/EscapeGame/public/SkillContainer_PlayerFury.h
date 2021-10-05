// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Component_SkillContainer.h"
#include "SkillActor_PlayerFury.h"
#include "SkillContainer_PlayerFury.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API USkillContainer_PlayerFury : public UComponent_SkillContainer
{
	GENERATED_BODY()
public:
	USkillContainer_PlayerFury();

	virtual void UseSkill(const AActor& TargetActor, const FVector& Direction, int n_Count = 1)override;
	void ActivateEffectAt(const FVector& At, int n_Count = 1);

protected:
	virtual void BeginPlay()override;


};
