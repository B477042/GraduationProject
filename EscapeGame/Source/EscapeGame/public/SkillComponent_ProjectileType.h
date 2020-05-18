// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Component_SkillContainer.h"
#include "SkillComponent_ProjectileType.generated.h"

/**TArray 내부에서 회전하듯 돌아가야 된다
 * 
 */
UCLASS()
class ESCAPEGAME_API USkillComponent_ProjectileType : public UComponent_SkillContainer
{
	GENERATED_BODY()
public:
	USkillComponent_ProjectileType();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

protected:

	

};
