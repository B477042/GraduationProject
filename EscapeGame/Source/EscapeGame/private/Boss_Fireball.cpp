// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss_Fireball.h"

ABoss_Fireball::ABoss_Fireball()
{
	loadAssets();
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
		MainEffect->SetTemplate(P_MAINEFFECT.Object);
		MainEffect->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>P_HITEFFECT(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Primary/FX/P_Gideon_Primary_HitCharacter.P_Gideon_Primary_HitCharacter'"));
	if (P_HITEFFECT.Succeeded())
	{
		HitEffect->SetTemplate(P_HITEFFECT.Object);
		HitEffect->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<USoundBase>SW_Passing(TEXT("SoundWave'/Game/MyFolder/Sound/248116__robinhood76__05224-fireball-whoosh.248116__robinhood76__05224-fireball-whoosh'"));
	if (SW_Passing.Succeeded())
	{
		SoundPassing->SetSound(SW_Passing.Object);
		SoundPassing->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<USoundBase>SW_Hit(TEXT("SoundWave'/Game/MyFolder/Sound/442872__qubodup__fire-magic.442872__qubodup__fire-magic'"));
	if (SW_Hit.Succeeded())
	{
		SoundHit->SetSound(SW_Hit.Object);
		SoundHit->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<USoundAttenuation >SA_Attenuation(TEXT("SoundAttenuation'/Game/MyFolder/Sound/FireBallCastAttenuation.FireBallCastAttenuation'"));
	if (SA_Attenuation.Succeeded())
	{
		SoundHit->AttenuationSettings = SA_Attenuation.Object;
		SoundPassing->AttenuationSettings = SA_Attenuation.Object;
	}

}
