// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SklillActor/SkillActor_PlayerFury.h"

#include "Engine/OverlapResult.h"

ASkillActor_PlayerFury::ASkillActor_PlayerFury()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem>P_Main(TEXT("ParticleSystem'/Game/ParagonKwang/FX/Particles/FX/P_Kwang_Recall_Burst.P_Kwang_Recall_Burst'"));
	if (P_Main.Succeeded())
	{
		VFX_Main->SetTemplate(P_Main.Object);
		VFX_Main->bAutoActivate = false;
		//(X = 5.750000, Y = 15.000000, Z = 1.750000)
		VFX_Main->SetRelativeScale3D(FVector(5.75f, 15.0f, 1.75f));
	}
	static ConstructorHelpers::FObjectFinder<USoundWave>SC_Main(TEXT("SoundWave'/Game/MyFolder/Sound/SE/thunder.thunder'"));
	if (SC_Main.Succeeded())
	{
		SFX_Hit->Sound=SC_Main.Object;
		SFX_Hit->bAutoActivate = false;
	}


}

void ASkillActor_PlayerFury::UseSkill(const FVector& Point)
{
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}
	SetActorHiddenInGame(false);
	Root->SetHiddenInGame(false);
	VFX_Main->SetHiddenInGame(false);

	FVector NewPoint = Point;
	NewPoint.Z += 300.0f;
	SetActorLocation(NewPoint);

	ActivateMainEffect();
	//SFX_Hit->SetHiddenInGame(false);
	SFX_Hit->Play();
	MainCollision->SetCollisionProfileName(TEXT("NoCollision"));

	//Ž���� ���������� �����
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FDamageEvent DamageEvent;
	TObjectPtr<APlayerController> playerCon = World->GetFirstPlayerController();
	if (!playerCon)
	{
		EGLOG(Error, TEXT("Cating fail"));
		return;
	}

	//PlayerCharacter�� Overlap �������� ã�Ƴ���. ����� DetectRadius���� ��
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Point, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(100.0f), CollisionQueryParam);
	if (bResult)
	{
		for (FOverlapResult& it : OverlapResults)
		{
			if (it.GetActor()->IsValidLowLevel())
			{
				it.GetActor()->TakeDamage(10.0f, DamageEvent, playerCon, GetOwner());
			}
			
			//EGLOG(Error, TEXT("Additional Damage To : %s"), *it.GetActor()->GetName());
		}
	}


}

void ASkillActor_PlayerFury::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SFX_Hit->OnAudioFinished.AddDynamic(this, &ASkillActor_PlayerFury::OnAudioFinished);
	//VFX_Main->OnSystemFinished.AddDynamic(this, &ASkillActor_PlayerFury::OnSystemEnd);
}

void ASkillActor_PlayerFury::OnAudioFinished()
{
	SetSafety(VFX_Main);
}


