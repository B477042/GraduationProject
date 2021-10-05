// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillContainer_PlayerFury.h"

USkillContainer_PlayerFury::USkillContainer_PlayerFury()
{
	ArraySize = 8;
	SkillObjects.SetNumZeroed(ArraySize);
	Index = 0;
}
void USkillContainer_PlayerFury::BeginPlay()
{
	Super::BeginPlay();
}



void USkillContainer_PlayerFury::UseSkill(const AActor& TargetActor, const FVector& Direction, int n_Count)
{
	auto Something = Cast<ASkillActor_PlayerFury>(CurrentIndex);
	if (!Something) {
		return;
		
	}

	Something->UseSkill(TargetActor.GetActorLocation());
	revolve();
}

void USkillContainer_PlayerFury::ActivateEffectAt(const FVector& At, int n_Count)
{
	auto Something = Cast<ASkillActor_PlayerFury>(CurrentIndex);
	if (!Something) {
		return;

	}

	Something->UseSkill(At);
	revolve();
}
