// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent_ProjectileType.h"
#include "Projectile.h"

USkillComponent_ProjectileType::USkillComponent_ProjectileType()
{
	ArraySize = 8;
	SkillObjects.SetNumZeroed(ArraySize);
	Index = 0;
}

void USkillComponent_ProjectileType::BeginPlay()
{
	Super::BeginPlay();
	//CurrentIndex = SkillObjects[0];
	Index = 0;
}

void USkillComponent_ProjectileType::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkillComponent_ProjectileType::UseSkill(const AActor & TargetActor, const FVector & Dir_Vector, int n_Count)
{
	EGLOG(Warning, TEXT("Aimming"));
	aimTo(Dir_Vector, n_Count);

}

void USkillComponent_ProjectileType::aimTo( const FVector & Dir_Vector, int n_Count)
{
	
	//πﬂªÁ√º
	EGLOG(Warning, TEXT("Aim Down Sight"));
	auto something=Cast<AProjectile>(CurrentIndex);
	if (!something) { 
		return;
		CurrentIndex = SkillObjects[Index];
	}

	EGLOG(Warning, TEXT("Aim Down Sight~"));
	something->ReadyToFire(Dir_Vector,GetOwner()->GetActorLocation(),GetOwner()->GetActorRotation());
	//someThing->
	

	revolve();
	
	
	
}
