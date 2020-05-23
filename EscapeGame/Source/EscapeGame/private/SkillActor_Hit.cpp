// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_Hit.h"

ASkillActor_Hit::ASkillActor_Hit()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Main(TEXT("ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Impact.P_Kwang_Primary_Impact'"));
	if (PS_Main.Succeeded())
	{
		MainEffect->SetTemplate(PS_Main.Object);
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
	SetActorLocation(Point);
	ActivateMainEffect();
	Collision->SetCollisionProfileName(TEXT("NoCollision"));
	
	EGLOG(Warning, TEXT("Play"));
}

void ASkillActor_Hit::OnSystemEnd(UParticleSystemComponent * PS)
{
	SetSafety();

}
