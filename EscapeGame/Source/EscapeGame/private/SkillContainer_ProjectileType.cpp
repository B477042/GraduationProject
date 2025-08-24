// Fill out your copyright notice in the Description page of Project Settings.



#include "Actor/SklillActor/SkillContainer_ProjectileType.h"

#include "Actor/Trap/Projectile.h"


USkillContainer_ProjectileType::USkillContainer_ProjectileType()
{
	ArraySize = 8;
	SkillObjects.SetNumZeroed(ArraySize);
	Index = 0;
}

void USkillContainer_ProjectileType::BeginPlay()
{
	Super::BeginPlay();
	//CurrentIndex = SkillObjects[0];
	Index = 0;
}

void USkillContainer_ProjectileType::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkillContainer_ProjectileType::UseSkill(const AActor & TargetActor, const FVector & Dir_Vector, int n_Count)
{
	
	aimTo(Dir_Vector, n_Count);

}

void USkillContainer_ProjectileType::BP_UseSkill(FVector Loc, FRotator Rot, FVector Dir)
{

	auto something = Cast<AProjectile>(CurrentIndex);
	if (!something) {
		return;
	
	}


	

	something->ReadyToFire(Dir, Loc, GetOwner()->GetActorRotation());
	//someThing->


	revolve();

}

void USkillContainer_ProjectileType::aimTo( const FVector & Dir_Vector, int n_Count)
{
	
	//�߻�ü
	
	auto something=Cast<AProjectile>(CurrentIndex);
	if (!something) { 
		return;
	
	}

	
	FVector FirePos = GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, 30.0f);

	something->ReadyToFire(Dir_Vector,FirePos,GetOwner()->GetActorRotation());
	//someThing->
	

	revolve();
	
	
	
}
