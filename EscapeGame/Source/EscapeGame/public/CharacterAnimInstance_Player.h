// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CharacterAnimInstance.h"
#include "CharacterAnimInstance_Player.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UCharacterAnimInstance_Player : public UCharacterAnimInstance
{
	GENERATED_BODY()
public:
	UCharacterAnimInstance_Player();
private:
	void JumpToComboAttackSection(int32 NewSection);//ComboAttack ���̸� ��� ��Ű�� �Լ�
	void JumpToChargetAttackSection(int32 NewSection);//ChargeAttack���� �Ѿ ChargeAttack�� �����Ű�� �Լ�
private:
	const int32 StartCombo = 1;//Attack Montage���� ó�� �׼� ��ȣ
	const int32 EndCombo = 4;//Attack Montage���� ������ �׼� ��ȣ

	//Charge Attack Montage
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ChargeAttackMontage;
};
