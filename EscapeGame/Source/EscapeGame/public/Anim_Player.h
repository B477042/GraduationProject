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
DECLARE_DELEGATE(FOnPlant);


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

	//Jog Play Rate ����. True : Running, False : Jog
	void SetJogPlayRate(bool bIsRunnuing);

	UFUNCTION()
		void AnimNotify_RollingStart();
	UFUNCTION()
		void AnimNotify_RollingEnd();
	UFUNCTION()
		void AnimNotify_AnimEnd();
	

	UFUNCTION()
		void AnimNotify_SkillStart();
	UFUNCTION()
		void AnimNotify_SkillEnd();
	UFUNCTION()
		void AnimNotify_AnimNotify_ThunderStart();
	UFUNCTION()
	void AnimNotify_DeadStart();
	UFUNCTION()
	void AnimNotify_DeadEnd();

	UFUNCTION()
		void AnimNotify_Plant();
	
	UFUNCTION()
		void AnimNotify_ReactDamagedEnd();
	
 

	//Input ���� Player�� Combo
	void PlaySkillMontage(int Combo);
	void SetGuarding(bool bResult) { bIsGuarding = bResult; }

	float GetRollingLength() { return RollingLength; }
	void SetDead();

	
	FOnPlant OnPlant;


private:
	//const int32 StartCombo = 1;//Attack Montage���� ó�� �׼� ��ȣ
	//const int32 EndCombo = 4;//Attack Montage���� ������ �׼� ��ȣ

	float RollingLength = 570.0f;

	

	////Charge Attack Montage
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	//	UAnimMontage* Montage_ChargeAttack;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		TArray<UAnimMontage*> Montage_Skills;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Montage_Roll;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Montage_Fury;


	UPROPERTY()
	UAudioComponent* SFX_Death;
	UPROPERTY()
	UAudioComponent* SFX_FootStep;


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
	
	//Walk Play rate property
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float CurrentJogPlayRate;

	UPROPERTY(VisibleDefaultsOnly,  Category = Character, Meta = (AllowPrivateAccess = true))
	float JogPlayRate;
	UPROPERTY(VisibleDefaultsOnly,  Category = Character, Meta = (AllowPrivateAccess = true))
	float RunningPlayRate;


};
