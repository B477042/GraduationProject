// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Projectile.h"
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
	
	virtual void BeginPlay() override;
	virtual void BeginDestroy()override;
	virtual void PostInitializeComponents() override;


	void loadAssets();
	void initCollisions();


};
