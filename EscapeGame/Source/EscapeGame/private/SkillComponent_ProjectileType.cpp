// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent_ProjectileType.h"
#include "Projectile.h"

USkillComponent_ProjectileType::USkillComponent_ProjectileType()
{

}

void USkillComponent_ProjectileType::BeginPlay()
{
	Super::BeginPlay();
}

void USkillComponent_ProjectileType::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkillComponent_ProjectileType::UseSkill(const AActor & TargetActor, const FVector & Dir_Vector, int n_Count)
{
	
	aimTo(Dir_Vector, n_Count);

}

void USkillComponent_ProjectileType::aimTo( const FVector & Dir_Vector, int n_Count)
{
	int i = 0;
	//πﬂªÁ√º
	while (i < n_Count)
	{
	auto something=Cast<AProjectile>(CurrentIndex);
	if (!something)return;

	something->ReadyToFire(Dir_Vector,GetOwner()->GetActorLocation(),GetOwner()->GetActorRotation());

	revolve();
	i++;
	}
	
}
