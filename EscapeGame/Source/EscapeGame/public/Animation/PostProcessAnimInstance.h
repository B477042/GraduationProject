// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PostProcessAnimInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ESCAPEGAME_API UPostProcessAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPostProcessAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
};
