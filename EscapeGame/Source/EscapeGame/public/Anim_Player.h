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
	virtual void NativeBeginPlay()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;



	virtual void JumpToComboAttackSection(int32 NewSection);//ComboAttack ���̸� ��� ��Ű�� �Լ�
	 void JumpToChargetAttackSection(int32 NewSection);//ChargeAttack���� �Ѿ ChargeAttack�� �����Ű�� �Լ�
	//Section���� Combo���� ��ġ �ϴ��� �˻��Ѵ�
	//��ġ ���� �ʴ´ٸ� Failed��� FName�� ��ȯ�ȴ�
	//	virtual FName GetAttackMontageSectionName(int32 Section);
	//void PlayAttackMontage();
	virtual void PlayAirAttackMontage();
	UAnimMontage* GetAttackMontage()const;
	void SetRolling(bool bResult);

	//������ ���� ��� ����. React Direction, bIsDamaged ����
	void TakeDamage(const AActor* OtherActor);


	UFUNCTION()
		void AnimNotify_RollingStart();
	UFUNCTION()
		void AnimNotify_RollingEnd();
	UFUNCTION()
		void AnimNotify_AnimEnd();
	UFUNCTION()
		void AnimNotify_PlayHitSound();

	UFUNCTION()
		void AnimNotify_Skill1Start();
	UFUNCTION()
		void AnimNotify_SkillEnd();
	UFUNCTION()
		void AnimNotify_AnimNotify_ThunderStart();
	UFUNCTION()
	void AnimNotify_DeadStart();
	UFUNCTION()
	void AnimNotify_DeadEnd();

	UFUNCTION()
		void AnimNotify_LeftPlant();
	UFUNCTION()
		void AnimNotify_RightPlant();
	UFUNCTION()
		void AnimNotify_ReactDamagedEnd();
	

	/*UFUNCTION()
		void OnMontageStart(UAnimMontage* Montage);
	UFUNCTION()
		void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);*/


	//Input ���� Player�� Combo
	void PlaySkillMontage(int Combo);
	void SetGuarding(bool bResult) { bIsGuarding = bResult; }

	float GetRollingLength() { return RollingLength; }
	void SetDead();
private:
	//const int32 StartCombo = 1;//Attack Montage���� ó�� �׼� ��ȣ
	//const int32 EndCombo = 4;//Attack Montage���� ������ �׼� ��ȣ

	float RollingLength = 570.0f;


	//Charge Attack Montage
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ChargeAttackMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		TArray<UAnimMontage*> SkillMontages;
	UPROPERTY()
	UAudioComponent* SFX_Laugh;

	UPROPERTY()
	UAudioComponent* SFX_Death;
	UPROPERTY()
	UAudioComponent* SFX_FootStep;
	UPROPERTY()
		UAudioComponent* SFX_Pain;

	////������ ��Ÿ��
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	//	UAnimMontage* AttackMontage;

	//���߰��� ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AirAttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		bool bIsRolling;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		bool bIsGuarding;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bIsDead;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		float Direction;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
		float ReactDirection;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bIsDamaged;



};
