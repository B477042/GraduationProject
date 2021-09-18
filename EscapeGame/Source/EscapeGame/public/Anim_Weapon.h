// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Animation/AnimInstance.h"
#include "Weapon.h"
#include "Anim_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UAnim_Weapon : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_Weapon();
	virtual void NativeBeginPlay()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;


protected:
	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<EWeaponTypes>WeaponType;
};
