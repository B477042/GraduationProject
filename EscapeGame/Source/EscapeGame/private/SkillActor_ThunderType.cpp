// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SklillActor/SkillActor_ThunderType.h"

#include "DrawDebugHelpers.h"
#include "Actor/Character/EGPlayerCharacter.h"
#include "Engine/OverlapResult.h"

ASkillActor_ThunderType::ASkillActor_ThunderType()
{
	loadAsset();
	VFX_Main->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	VFX_Hit->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	Damage = 300.0f;
}


void ASkillActor_ThunderType::loadAsset()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Main(TEXT("ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/LightStrike/FX/P_Kwang_LightStrike_Burst.P_Kwang_LightStrike_Burst'"));
	if (PS_Main.Succeeded())
	{
		VFX_Main->SetTemplate(PS_Main.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Hit(TEXT("ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/LightStrike/FX/P_Kwang_LightStrike_Burst_Holding.P_Kwang_LightStrike_Burst_Holding'"));
	if (PS_Hit.Succeeded())
	{
		VFX_Hit->SetTemplate(PS_Hit.Object);
	}
	//SoundWave'/Game/MyFolder/Sound/thunder.thunder'
	static ConstructorHelpers::FObjectFinder<USoundBase>SO(TEXT("SoundWave'/Game/MyFolder/Sound/SE/thunder.thunder'"));
	if (SO.Succeeded())
	{
		SFX_Hit->SetSound(SO.Object);
	}

}

void ASkillActor_ThunderType::BeginPlay()
{
	Super::BeginPlay();
}

void ASkillActor_ThunderType::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	VFX_Hit->OnSystemFinished.AddDynamic(this, &ASkillActor_ThunderType::OnSystemEnd);

}

void ASkillActor_ThunderType::OnSystemEnd(UParticleSystemComponent * PS)
{
	SetSafety(PS);
}


void ASkillActor_ThunderType::UseSkill(const FVector & Location)
{
	SetActorHiddenInGame(false);
	VFX_Main->SetHiddenInGame(false);
	VFX_Main->Activate();
	VFX_Hit->SetHiddenInGame(false);
	VFX_Hit->Activate();
	SetActorLocation(Location);
	SFX_Hit->Play();

	TArray<FHitResult> HitResult;

	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this );

	auto World = GetWorld();
	if (World == nullptr)return;

	FVector HitBoxRadius = FVector(300.0f, 300.0f, 100.0f);

	//PlayerCharacter�� Overlap �������� ã�Ƴ���. ����� DetectRadius���� ��
	bool bResult = World->OverlapMultiByChannel(OverlapResults, GetActorLocation()+FVector(0.0f,0.0f,HitBoxRadius.Z), FQuat::Identity, ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeBox(HitBoxRadius), CollisionQueryParam);
	FDamageEvent DamageEvent;
	if (bResult)
	{
		EGLOG(Warning, TEXT("Ovbepasdf"));
		for (FOverlapResult&  OverlapResult : OverlapResults)
		{
			auto player = Cast<AEGPlayerCharacter>(OverlapResult.GetActor());
			if (player)continue;
			/*
			DrawDebugPoint(World, OverlapResult.Actor->GetTargetPlayerLocation(), 100.0f, FColor::Red, false, 0.2f);
			EGLOG(Error, TEXT(" Hit Actor : %s , Damage : %d"), *OverlapResult.Actor->GetName(),Damage);*/
			
			OverlapResult.GetActor()->TakeDamage(Damage,DamageEvent,World->GetFirstPlayerController(),this);


		}
	}
	

}