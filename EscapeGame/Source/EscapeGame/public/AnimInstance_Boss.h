// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyBossCharacter.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Boss.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UAnimInstance_Boss : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInstance_Boss();


private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bIsInAir;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float CurrentSpeed;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Pitch;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Yaw;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Roll;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float YawDelta;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		AEnemyBossCharacter* OwnerChara;

};
