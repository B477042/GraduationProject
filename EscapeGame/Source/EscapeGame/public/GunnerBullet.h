// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Projectile.h"
//#include "Components/AudioComponent.h"
//#include "Components/SphereComponent.h"
//#include "Particles/ParticleSystemComponent.h"
#include "GunnerBullet.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AGunnerBullet : public AProjectile
{
	GENERATED_BODY()
public:
	AGunnerBullet();

protected:
	// ==============================Form AActor=====================
	virtual void BeginPlay() override;
	virtual void BeginDestroy()override;
	virtual void PostInitializeComponents() override;


	void loadAssets();
	void initCollisions();

private:
	
	

};
