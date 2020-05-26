// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_ThunderType.h"
#include "EGPlayerCharacter.h"
#include "DrawDebugHelpers.h"

ASkillActor_ThunderType::ASkillActor_ThunderType()
{
	loadAsset();
	MainEffect->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	HitEffect->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	Damage = 300.0f;
}


void ASkillActor_ThunderType::loadAsset()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Main(TEXT("ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/LightStrike/FX/P_Kwang_LightStrike_Burst.P_Kwang_LightStrike_Burst'"));
	if (PS_Main.Succeeded())
	{
		MainEffect->SetTemplate(PS_Main.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Hit(TEXT("ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/LightStrike/FX/P_Kwang_LightStrike_Burst_Holding.P_Kwang_LightStrike_Burst_Holding'"));
	if (PS_Hit.Succeeded())
	{
		HitEffect->SetTemplate(PS_Hit.Object);
	}
	//SoundWave'/Game/MyFolder/Sound/thunder.thunder'
	static ConstructorHelpers::FObjectFinder<USoundBase>SO(TEXT("SoundWave'/Game/MyFolder/Sound/thunder.thunder'"));
	if (SO.Succeeded())
	{
		SoundHit->SetSound(SO.Object);
	}

}

void ASkillActor_ThunderType::BeginPlay()
{
	Super::BeginPlay();
}

void ASkillActor_ThunderType::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HitEffect->OnSystemFinished.AddDynamic(this, &ASkillActor_ThunderType::OnSystemEnd);

}

void ASkillActor_ThunderType::OnSystemEnd(UParticleSystemComponent * PS)
{
	SetSafety();
}


void ASkillActor_ThunderType::UseSkill(const FVector & Location)
{
	SetActorHiddenInGame(false);
	MainEffect->SetHiddenInGame(false);
	MainEffect->Activate();
	HitEffect->SetHiddenInGame(false);
	HitEffect->Activate();
	SetActorLocation(Location);
	SoundHit->Play();

	TArray<FHitResult> HitResult;

	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this );

	auto World = GetWorld();
	if (World == nullptr)return;

	FVector HitBoxRadius = FVector(300.0f, 300.0f, 100.0f);

	//PlayerCharacter를 Overlap 반응으로 찾아낸다. 모양은 DetectRadius만한 구
	bool bResult = World->OverlapMultiByChannel(OverlapResults, GetActorLocation()+FVector(0.0f,0.0f,HitBoxRadius.Z), FQuat::Identity, ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeBox(HitBoxRadius), CollisionQueryParam);
	FDamageEvent DamageEvent;
	if (bResult)
	{
		EGLOG(Warning, TEXT("Ovbepasdf"));
		for (auto OverlapResult : OverlapResults)
		{
			auto player = Cast<AEGPlayerCharacter>(OverlapResult.Actor);
			if (player)continue;
			/*
			DrawDebugPoint(World, OverlapResult.Actor->GetTargetLocation(), 100.0f, FColor::Red, false, 0.2f);
			EGLOG(Error, TEXT(" Hit Actor : %s , Damage : %d"), *OverlapResult.Actor->GetName(),Damage);*/
			
			OverlapResult.Actor->TakeDamage(Damage,DamageEvent,World->GetFirstPlayerController(),this);


		}
	}
	

}