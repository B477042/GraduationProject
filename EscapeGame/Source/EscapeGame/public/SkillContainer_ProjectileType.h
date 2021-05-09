// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Component_SkillContainer.h"
#include "SkillContainer_ProjectileType.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class ESCAPEGAME_API USkillContainer_ProjectileType : public UComponent_SkillContainer
{
	GENERATED_BODY()
public:
	USkillContainer_ProjectileType();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//발사체 스킬을 사용한다.
	
	virtual void UseSkill(const AActor& TargetActor, const FVector& Dir_Vector, int n_Count = 1);

	UFUNCTION(BlueprintCallable)
		void BP_UseSkill(FVector Loc, FRotator Rot, FVector Dir);

protected:
	void aimTo(const FVector& Dir_Vector,int n_Count);
	

};
