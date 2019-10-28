// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnimInstance.h"


UCharacterAnimInstance::UCharacterAnimInstance()
{
	CurrentCharacterSpeed = 0.0f;
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentCharacterSpeed = Pawn->GetVelocity().Size();
	}
}
