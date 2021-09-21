// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Weapon.h"

UAnim_Weapon::UAnim_Weapon()
{

}

void UAnim_Weapon::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	

}

void UAnim_Weapon::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UAnim_Weapon::AnimNotify_OnEjectionEnd()
{
	OnEjectionEnd.Execute();
	bIsFired = false;
}

