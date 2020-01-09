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
DECLARE_MULTICAST_DELEGATE(FComboAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FChargeAttackCheckDelegate);

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
	//montage 플레이를 테스트 해보자. 된다면 CharageAttack용 몽타주를 안 만들어도 된다.
	void PlayNormalAttackMontage();
	void JumpToComboAttackSection(int32 NewSection);//ComboAttack 사이를 재생 시키는 함수
	void JumpToChargetAttackSection(int32 NewSection);//ChargeAttack으로 넘어가 ChargeAttack을 재생시키는 함수

	FComboAttackCheckDelegate OnComboAttackCheckDelegate;
	FChargeAttackCheckDelegate OnChargeAttackCheckDelegate;
private:
	UFUNCTION()
		void AnimNotify_CanNextAttack();
	UFUNCTION()
		void AnimNotify_CanChargeAttack();
	FName GetComboMontageSectionName(int32 Section);
	/*UFUNCTION(BlueprintCallable)
		void Switch;*/
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


	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	//	TWeakObjectPtr<AEGPlayerCharacter> Character;//나중에 안 쓰면 그냥 지우고
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;//통상공격 몽타주

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
		bool IsJumpPressed;*/

};
/*
	2020 01 03 - 원하는 것
	완벽하게 구별되는 
*/