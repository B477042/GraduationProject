// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CharacterAnimInstance.h"
#include "Anim_Player.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FPlayerRollingStartDelegate);
DECLARE_MULTICAST_DELEGATE(FPlayerRollingEndDelegate);


UCLASS()
class ESCAPEGAME_API UAnim_Player : public UCharacterAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_Player();

	virtual void JumpToComboAttackSection(int32 NewSection);//ComboAttack 사이를 재생 시키는 함수
	 void JumpToChargetAttackSection(int32 NewSection);//ChargeAttack으로 넘어가 ChargeAttack을 재생시키는 함수
	//Section값이 Combo값과 일치 하는지 검사한다
//일치 하지 않는다면 Failed라는 FName이 반환된다
//	virtual FName GetAttackMontageSectionName(int32 Section);
	//void PlayAttackMontage();
	virtual void PlayAirAttackMontage();
	UAnimMontage* GetAttackMontage()const;
	void SetRolling(bool bResult);

	UFUNCTION()
		void AnimNotify_RollingStart();
	UFUNCTION()
		void AnimNotify_RollingEnd();
	UFUNCTION()
		void AnimNotify_AnimEnd();
	UFUNCTION()
		void AnimNotify_PlaySound();

	UFUNCTION()
		void AnimNotify_Skill1Start();
	UFUNCTION()
		void AnimNotify_SkillEnd();
	UFUNCTION()
		void AnimNotify_AnimNotify_ThunderStart();

	//Input 값은 Player의 Combo
	void PlaySkillMontage(int Combo);

	float GetRollingLength() { return RollingLength; }
private:
	//const int32 StartCombo = 1;//Attack Montage에서 처음 액션 번호
	//const int32 EndCombo = 4;//Attack Montage에서 마지막 액션 번호

	float RollingLength = 570.0f;


	//Charge Attack Montage
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ChargeAttackMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		TArray<UAnimMontage*> SkillMontages;
	UPROPERTY()
		UAudioComponent* SoundLaugh;

	////통상공격 몽타주
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	//	UAnimMontage* AttackMontage;

	//공중공격 몽타주
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AirAttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		bool bIsRolling;
};
