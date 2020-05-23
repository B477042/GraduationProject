// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "SkillActor.h"
#include "SkillActor_ThunderType.generated.h"

/**
 * Player Skill ¿¬Ãâ¿ë
 */
UCLASS()
class ESCAPEGAME_API ASkillActor_ThunderType : public ASkillActor
{
	GENERATED_BODY()
public:

	ASkillActor_ThunderType();
	void UseSkill(const FVector& Location);
protected:
	void loadAsset();
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
	UFUNCTION()
		void OnSystemEnd(UParticleSystemComponent *PS);
	//
	float DamageRate;
};
