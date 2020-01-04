// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnimInstance.h"
#include "..\public\CharacterAnimInstance.h"


UCharacterAnimInstance::UCharacterAnimInstance()
{
	CurrentCharacterSpeed = 0.0f;
	PriviousCharacterHight = 0.0f;
	HightVariation = 0.0f;
	IsInAir = false;
	
}


void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentCharacterSpeed = Pawn->GetVelocity().Size();
		HightVariation = Pawn->GetActorLocation().Z - PriviousCharacterHight;
		PriviousCharacterHight = Pawn->GetActorLocation().Z;
		

		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}

	}
}

void UCharacterAnimInstance::BPBeginPlay()
{
	EGLOG(Warning, TEXT("Anim Blueprint Begin!!!"));
	EGLOG(Warning, TEXT("Anim Bp Owner name : %s"), *GetOwningActor()->GetName());
}

