// Fill out your copyright notice in the Description page of Project Settings.



#include "Actor/SklillActor/Boss_Fireball.h"

ABoss_Fireball::ABoss_Fireball()
{
	loadAssets();
	SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));
	Damage = 6;
	Acceleration = 30.0f;
}

void ABoss_Fireball::ReadyToFire(const FVector & Dir_Vector, const FVector & Location, const FRotator & Rotate)
{
	Super::ReadyToFire(Dir_Vector, Location, Rotate);

}

void ABoss_Fireball::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABoss_Fireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoss_Fireball::BeginPlay()
{
	Super::BeginPlay();
}

void ABoss_Fireball::loadAssets()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem>P_MAINEFFECT(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_Projectile.P_Gideon_Primary_Projectile'"));
	if (P_MAINEFFECT.Succeeded())
	{
		VFX_Main->SetTemplate(P_MAINEFFECT.Object);
		VFX_Main->bAutoActivate = false;

	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>P_HITEFFECT(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_HitCharacter.P_Gideon_Primary_HitCharacter'"));
	if (P_HITEFFECT.Succeeded())
	{
		VFX_Hit->SetTemplate(P_HITEFFECT.Object);
		VFX_Hit->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<USoundBase>SW_Passing(TEXT("SoundWave'/Game/MyFolder/Sound/SE/248116__robinhood76__05224-fireball-whoosh.248116__robinhood76__05224-fireball-whoosh'"));
	if (SW_Passing.Succeeded())
	{
		SFX_Passing->SetSound(SW_Passing.Object);
		SFX_Passing->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<USoundBase>SW_Hit(TEXT("SoundWave'/Game/MyFolder/Sound/SE/442872__qubodup__fire-magic.442872__qubodup__fire-magic'"));
	if (SW_Hit.Succeeded())
	{
		SFX_Hit->SetSound(SW_Hit.Object);
		SFX_Hit->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<USoundAttenuation >SA_Attenuation(TEXT("SoundAttenuation'/Game/MyFolder/Sound/FireBallCastAttenuation.FireBallCastAttenuation'"));
	if (SA_Attenuation.Succeeded())
	{
		SFX_Hit->AttenuationSettings = SA_Attenuation.Object;
		SFX_Passing->AttenuationSettings = SA_Attenuation.Object;
	}

}
