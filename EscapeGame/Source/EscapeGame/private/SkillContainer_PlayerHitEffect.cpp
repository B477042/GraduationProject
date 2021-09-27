// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillContainer_PlayerHitEffect.h"



USkillContainer_PlayerHitEffect::USkillContainer_PlayerHitEffect()
{

	ArraySize = 8;
	SkillObjects.SetNumZeroed(ArraySize);
	Index = 0;
}

void USkillContainer_PlayerHitEffect::BeginPlay()
{
	Super::BeginPlay();

}

void USkillContainer_PlayerHitEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
//Hit 이펙트가 아닌 무언가를 넣으면 동작하지 않는다
void USkillContainer_PlayerHitEffect::UseSkill(const AActor & TargetActor, const FVector & Direction, int n_Count)
{
	auto something = Cast<ASkillActor_Hit>(CurrentIndex);
	if (!something) {
		return;
		//CurrentIndex = SkillObjects[Index];
	}

	something->UseSkill(TargetActor.GetActorLocation());
	revolve();
}

void USkillContainer_PlayerHitEffect::ActivateEffectAt(const FVector & At, int n_Count)
{
	auto something = Cast<ASkillActor_Hit>(CurrentIndex);
	if (!something) {
		return;
		//CurrentIndex = SkillObjects[Index];
	}

	something->UseSkill(At);
	revolve();

}
