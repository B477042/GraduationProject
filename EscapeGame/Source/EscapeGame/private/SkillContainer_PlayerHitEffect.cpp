// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SklillActor/SkillContainer_PlayerHitEffect.h"

#include "Actor/SklillActor/SkillActor_Hit.h"

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
//Hit ����Ʈ�� �ƴ� ���𰡸� ������ �������� �ʴ´�
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
