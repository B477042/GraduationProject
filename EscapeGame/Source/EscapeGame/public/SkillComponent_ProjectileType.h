// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Component_SkillContainer.h"
#include "SkillComponent_ProjectileType.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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
	//발사체 스킬을 사용한다.
	
	virtual void UseSkill(const AActor& TargetActor, const FVector& Dir_Vector, int n_Count = 1);

protected:
	void aimTo(const FVector& Dir_Vector,int n_Count);
	

};
