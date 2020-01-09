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
	//montage �÷��̸� �׽�Ʈ �غ���. �ȴٸ� CharageAttack�� ��Ÿ�ָ� �� ���� �ȴ�.
	void PlayNormalAttackMontage();
	void JumpToComboAttackSection(int32 NewSection);//ComboAttack ���̸� ��� ��Ű�� �Լ�
	void JumpToChargetAttackSection(int32 NewSection);//ChargeAttack���� �Ѿ ChargeAttack�� �����Ű�� �Լ�

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
		bool IsAccelerating;//Character��  ���������� üũ


	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	//	TWeakObjectPtr<AEGPlayerCharacter> Character;//���߿� �� ���� �׳� �����
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;//������ ��Ÿ��

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
		bool IsJumpPressed;*/

};
/*
	2020 01 03 - ���ϴ� ��
	�Ϻ��ϰ� �����Ǵ� 
*/