// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent_ProjectileType.h"

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
