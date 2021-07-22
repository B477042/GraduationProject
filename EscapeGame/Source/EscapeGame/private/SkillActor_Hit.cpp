// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_Hit.h"
#include "Sound/SoundCue.h"
#include "EGPlayerCharacter.h"


ASkillActor_Hit::ASkillActor_Hit()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Main(TEXT("ParticleSystem'/Game/ParagonHowitzer/FX/Particles/Abilities/LRM/FX/P_LRM_Explo_Character_Miss.P_LRM_Explo_Character_Miss'"));
	if (PS_Main.Succeeded())
	{
		VFX_Main->SetTemplate(PS_Main.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundCue>SC_Effect(TEXT("SoundCue'/Game/MyFolder/Sound/SE/CUE_GroundExplosion.CUE_GroundExplosion'"));
	if (SC_Effect.Succeeded())
	{
		SFX_Hit->SetSound(SC_Effect.Object);

	}


}

void ASkillActor_Hit::BeginPlay()
{
	Super::BeginPlay();

}

void ASkillActor_Hit::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	VFX_Main->OnSystemFinished.AddDynamic(this, &ASkillActor_Hit::OnSystemEnd);
}

void ASkillActor_Hit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkillActor_Hit::UseSkill(const FVector & Point)
{
	SetActorHiddenInGame(false);
	Root->SetHiddenInGame(false);
	VFX_Main->SetHiddenInGame(false);
	SetActorLocation(Point);

	ActivateMainEffect();
	//SFX_Hit->SetHiddenInGame(false);
	SFX_Hit->Play();
	MainCollision->SetCollisionProfileName(TEXT("NoCollision"));
	
	//탐지된 여러가지의 결과들
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FDamageEvent DamageEvent;
	auto playerCon = GetWorld()->GetFirstPlayerController();
	//PlayerCharacter를 Overlap 반응으로 찾아낸다. 모양은 DetectRadius만한 구
	bool bResult = GetWorld()->OverlapMultiByChannel(OverlapResults, Point, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f), CollisionQueryParam);
	if (bResult)
	{
		for (auto it : OverlapResults)
		{
			it.GetActor()->TakeDamage(10.0f, DamageEvent, playerCon, this);
			EGLOG(Error, TEXT("Additional Damage To : %s"), *it.GetActor()->GetName());
		}
	}


}

void ASkillActor_Hit::OnSystemEnd(UParticleSystemComponent * PS)
{
	SetSafety(PS);

}
