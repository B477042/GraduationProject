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
	//dont override it. if override, Write down Super at first
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
	//virtual void PostInitalizeComponents()override;

	UFUNCTION(BlueprintCallable)
		void BPBeginPlay();
	//UFUNCTION(BlueprintCallable)
	//	void UpdateIsMoving();
	//montage 플레이를 테스트 해보자. 된다면 CharageAttack용 몽타주를 안 만들어도 된다.

	
	

	FComboAttackCheckDelegate OnComboAttackCheckDelegate;//콤보 어택으로 이어질지 검사하는 델리게이트
	FChargeAttackCheckDelegate OnChargeAttackCheckDelegate;//차지어택으로 이어질지 검사하는 델리게이트
	
	//AnimNotify는 몽타쥬에서 정한 호출 시점에서 자동으로 호출된다
	UFUNCTION()
		void AnimNotify_CanComboAttack();
	UFUNCTION()
		void AnimNotify_CanChargeAttack();

	//Pure Virtual func
	virtual FName GetAttackMontageSectionName(int32 Section) PURE_VIRTUAL(UCharacterAnimInstance::GetAttackMontageSectionName , return FName(TEXT("NULL")); );
	virtual void JumpToComboAttackSection(int32 NewSection) PURE_VIRTUAL(UCharacterAnimInstance::JumpToComboAttackSection, ;);
	virtual void JumpToChargetAttackSection(int32 NewSection) PURE_VIRTUAL(UCharacterAnimInstance::JumpToChargetAttackSection, ;);
	virtual void PlayAttackMontage() PURE_VIRTUAL(UCharacterAnimInstance::PlayAttackMontage, ;);
	virtual void PlayAirAttackMontage() PURE_VIRTUAL(UCharacterAnimInstance::PlayAirAttackMontage, ;);
	/*UFUNCTION(BlueprintCallable)
		void Switch;*/

protected:
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
	//	bool IsAccelerating;//Character가  가속중인지 체크


	
	////통상공격 몽타주
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	//	UAnimMontage* AttackMontage;
	//
	////공중공격 몽타주
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	//	UAnimMontage* AirAttackMontage;
	//Attack Montage에서 처음 액션 번호
	 int32 StartCombo;
	//Attack Montage에서 마지막 액션 번호
	 int32 EndCombo;

	
};
/*
	2020 
*/