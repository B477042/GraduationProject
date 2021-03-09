// Fill out your copyright notice in the Description page of Project Settings.


#include "GunnerBullet.h"

AGunnerBullet::AGunnerBullet()
{
	
	loadAssets();
	initCollisions();
	Damage = 2.5f;
}

void AGunnerBullet::BeginPlay()
{
	Super::BeginPlay();

	//MainCollision->OnComponentBeginOverlap.
}

void AGunnerBullet::BeginDestroy()
{
	Super::BeginDestroy();

}

void AGunnerBullet::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AGunnerBullet::loadAssets()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Main(TEXT("ParticleSystem'/Game/ParagonHowitzer/FX/Particles/Abilities/LRM/FX/V2/P_H_LRM_BulletTrailV2.P_H_LRM_BulletTrailV2'"));
	if (PS_Main.Succeeded())
	{
		VFX_Main->SetTemplate( PS_Main.Object);
		VFX_Main->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	}


	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Hit(TEXT("ParticleSystem'/Game/ParagonHowitzer/FX/Particles/Abilities/Primary/FX/P_Grenade_Muzzle.P_Grenade_Muzzle'"));
	if (PS_Hit.Succeeded())
	{
		VFX_Hit->SetTemplate(PS_Hit.Object);
	}
		


}

void AGunnerBullet::initCollisions()
{
	MainCollision->SetSphereRadius(45.0f);

}



	


