// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "Actor/Trap/Projectile.h"
#include "Boss_Fireball.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API ABoss_Fireball : public AProjectile
{
	GENERATED_BODY()
public:
	ABoss_Fireball();
	virtual void ReadyToFire(const FVector &Dir_Vector, const FVector& Location, const FRotator& Rotate) override;
	virtual void PostInitializeComponents()override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	void loadAssets();


};
