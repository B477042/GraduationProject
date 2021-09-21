// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Animation/AnimInstance.h"
#include "Weapon.h"
#include "Anim_Weapon.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOnEjectionEnd);

UCLASS()
class ESCAPEGAME_API UAnim_Weapon : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_Weapon();
	virtual void NativeBeginPlay()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
	
	void SetIsFired(bool NewValue) { bIsFired = NewValue; }

	FOnEjectionEnd OnEjectionEnd;

protected:

	UFUNCTION()
		void AnimNotify_OnEjectionEnd();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Variables", meta = (AllowPrivateAccess = true))
		bool bIsFired;

	

};
