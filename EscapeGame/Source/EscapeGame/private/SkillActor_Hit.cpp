// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_Hit.h"
#include "Sound/SoundCue.h"

ASkillActor_Hit::ASkillActor_Hit()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Main(TEXT("ParticleSystem'/Game/ParagonHowitzer/FX/Particles/Abilities/LRM/FX/P_LRM_Explo_Character_Miss.P_LRM_Explo_Character_Miss'"));
	if (PS_Main.Succeeded())
	{
		MainEffect->SetTemplate(PS_Main.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundCue>SC_Effect(TEXT("SoundCue'/Game/MagicModule/SFX/CUE/CUE_GroundExplosion.CUE_GroundExplosion'"));
	if (SC_Effect.Succeeded())
	{
		SoundHit->SetSound(SC_Effect.Object);

	}


}

void ASkillActor_Hit::BeginPlay()
{
	Super::BeginPlay();

}

void ASkillActor_Hit::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MainEffect->OnSystemFinished.AddDynamic(this, &ASkillActor_Hit::OnSystemEnd);
}

void ASkillActor_Hit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkillActor_Hit::UseSkill(const FVector & Point)
{
	SetActorHiddenInGame(false);
	Root->SetHiddenInGame(false);
	MainEffect->SetHiddenInGame(false);
	SetActorLocation(Point);

	ActivateMainEffect();
	//SoundHit->SetHiddenInGame(false);
	SoundHit->Play();
	Collision->SetCollisionProfileName(TEXT("NoCollision"));
	//SetActorHiddenInGame(false);
	EGLOG(Warning, TEXT("Play : %s"),*Point.ToString());
}

void ASkillActor_Hit::OnSystemEnd(UParticleSystemComponent * PS)
{
	SetSafety();

}
