// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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



	//void NativeBeginPlay();

	UFUNCTION()
	void AnimNotify_DeadStart();
	UFUNCTION()
	void AnimNotify_DeadEnd();
	UFUNCTION()
	void AnimNotify_ChargeStart();
	UFUNCTION()
	void AnimNotify_ChargeEnd();

	void PlayChargeAnim();
	

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Yaw_0;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Pitch_0;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Roll_0;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Yaw_Delta;

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
	//UPROPERTY(VisibleAnywhere, Category = "Mp", meta = (AllowPrivateAccess = "true"))
	//UAnimMontage* HealMontage;




	//AnimSequence'/Game/ParagonGideon/Characters/Heroes/Gideon/Animations/Death_Back.Death_Back'


};
