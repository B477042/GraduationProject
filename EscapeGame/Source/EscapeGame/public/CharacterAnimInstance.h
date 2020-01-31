// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Animation/AnimInstance.h"
//#include "EGPlayerCharacter.h"
#include "CharacterAnimInstance.generated.h"

/**
 * Use for Animation blueprint
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
protected:
	void PlayAttackMontage();
	void PlayAirAttackMontage();
	virtual void JumpToComboAttackSection(int32 NewSection);
	virtual void JumpToChargetAttackSection(int32 NewSection);

	FComboAttackCheckDelegate OnComboAttackCheckDelegate;//�޺� �������� �̾����� �˻��ϴ� ��������Ʈ
	FChargeAttackCheckDelegate OnChargeAttackCheckDelegate;//������������ �̾����� �˻��ϴ� ��������Ʈ

	//AnimNotify�� ��Ÿ�꿡�� ���� ȣ�� �������� �ڵ����� ȣ��ȴ�
	UFUNCTION()
		void AnimNotify_CanComboAttack();
	UFUNCTION()
		void AnimNotify_CanChargeAttack();

	FName GetAttackMontageSectionName(int32 Section);
	/*UFUNCTION(BlueprintCallable)
		void Switch;*/


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		float CurrentCharacterSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		float HightVariation;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		float PriviousCharacterHight;

	//is Character in air?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		bool IsInAir;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	//	bool IsAccelerating;//Character��  ���������� üũ


	
	//������ ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;
	
	//���߰��� ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AirAttackMontage;

	

	
};
/*
	2020 01 03 - ���ϴ� ��
	�Ϻ��ϰ� �����Ǵ� 
*/