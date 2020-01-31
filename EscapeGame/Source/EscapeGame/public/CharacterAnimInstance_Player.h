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
	void JumpToComboAttackSection(int32 NewSection);//ComboAttack 사이를 재생 시키는 함수
	void JumpToChargetAttackSection(int32 NewSection);//ChargeAttack으로 넘어가 ChargeAttack을 재생시키는 함수
private:
	const int32 StartCombo = 1;//Attack Montage에서 처음 액션 번호
	const int32 EndCombo = 4;//Attack Montage에서 마지막 액션 번호

	//Charge Attack Montage
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ChargeAttackMontage;
};
