// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Animation/AnimInstance.h"
#include "EGPlayerCharacter.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FAttackEventDelegate);

UCLASS()
class ESCAPEGAME_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UCharacterAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
	//virtual void PostInitalizeComponents()override;

	UFUNCTION(BlueprintCallable)
		void BPBeginPlay();
	//UFUNCTION(BlueprintCallable)
	//	void UpdateIsMoving();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		float CurrentCharacterSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		float HightVariation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		float PriviousCharacterHight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		bool IsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		bool IsAccelerating;//Character가  가속중인지 체크


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		TWeakObjectPtr<AEGPlayerCharacter> Character;
		
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
		bool IsJumpPressed;*/

};
/*
	2020 01 03 - 원하는 것
	완벽하게 구별되는 
*/