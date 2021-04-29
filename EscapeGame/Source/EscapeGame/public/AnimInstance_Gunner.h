// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Animation/AnimInstance.h"
#include "EnemyCharacter_Gunner.h"
#include "Sound/SoundBase.h"
#include "AnimInstance_Gunner.generated.h"

/**
 * 
 */



UCLASS()
class ESCAPEGAME_API UAnimInstance_Gunner : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInstance_Gunner();
protected:
	virtual void NativeBeginPlay()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
	

public:

	void SetCrouch(bool bSet);
	void SetIronsights(bool bSet);
	void SetAttacking(bool bSet);
	void SetAccelerating(bool bSet);
	void SetDead(bool bSet);

	UAnimMontage* GetFireMontage()const;

	void PlayFire(EGunnerState State);
	void PlayReload(EGunnerState State);

	UFUNCTION()
		void AnimNotify_Anim_DeadStart();
	UFUNCTION()
		void AnimNotify_Anim_DeadEnd();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	bool bIsFullBody;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	bool bIsCrouch;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	bool bOnIronsights;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	bool bIsDead;


	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	float Speed;
	/*UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	float bs_Speed;*/
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	float Direction;


	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	AEnemyCharacter_Gunner* Character;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	float Pitch;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	float  Roll; 
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	float Yaw;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	float YawDelta;
	/*UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	float AimPitch;
	UPROPERTY(BlueprintReadOnly, Category = "variable", meta = (AllowPrivateAccess = "true"))
	float AimYaw;*/

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FireMontage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SFX", meta = (AllowPrivateAccess = true))
		USoundBase* SFX_Dead;


	FRotator RotationLastTick;
	FVector PrevPos;
	

	static const FName FIRE_RIFLE_IRONSIGHTS;
	static const FName FIRE_RIFLE_HIP;
	static const FName RELOAD_RIFLE_HIP;
	static const FName RELOAD_RIFLE_IRONSIGHTS;

};
