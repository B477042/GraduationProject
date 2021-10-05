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
	 
	virtual void PlayAirAttackMontage();
	UAnimMontage* GetAttackMontage()const;
	void SetRolling(bool bResult);

	//������ ���� ��� ����. React Direction, bIsDamaged ����
	void TakeDamage(const AActor* OtherActor);

	//Jog Play Rate ����. True : Running, False : Jog
	void SetJogPlayRate(bool bIsRunnuing);
	//When rolling strat
	UFUNCTION()
		void AnimNotify_RollingStart();
	//When rolling end
	UFUNCTION()
		void AnimNotify_RollingEnd();
	
	UFUNCTION()
		void AnimNotify_AnimEnd();
	
	//On Skill Montage Start
	UFUNCTION()
		void AnimNotify_SkillStart();
	//On Skill Montage End
	UFUNCTION()
		void AnimNotify_SkillEnd();
	//On Thunder called. Skill 3
	UFUNCTION()
		void AnimNotify_AnimNotify_ThunderStart();
	//On Dead Animation Start
	UFUNCTION()
	void AnimNotify_DeadStart();
	//On Dead Animation end
	UFUNCTION()
	void AnimNotify_DeadEnd();
	//When Play Plant
	UFUNCTION()
		void AnimNotify_Plant();
	
	UFUNCTION()
		void AnimNotify_ReactDamagedEnd();
	//Skill 1 Damage Check
	UFUNCTION()
		void AnimNotify_Skill1Check();
	//Skill 2 Buff
	UFUNCTION()
		void AnimNotify_BuffActive();
	//OnFury Montage Start
	UFUNCTION()
		void AnimNotify_FuryStart();
	//Active Left Arm Particle
	UFUNCTION()
		void AnimNotify_FuryLeftArm();
	//Active Right Arm Particle
	UFUNCTION()
		void AnimNotify_FuryRightArm();
	//Extend Particle on Arms
	UFUNCTION()
		void AnimNotify_FuryExtend();
	//Apply damage to enemies
	UFUNCTION()
		void AnimNotify_FuryDamage();
	//OnFury Montage End
	UFUNCTION()
		void AnimNotify_FuryEnd();


	//Input ���� Player�� Combo
	void PlaySkillMontage(int Combo);
	void SetGuarding(bool bResult) { bIsGuarding = bResult; }

	float GetRollingLength() { return RollingLength; }
	void SetDead();

	
	FOnPlant OnPlant;

	void PlayFury();

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

	UPROPERTY()
		TWeakObjectPtr<class AEGPlayerCharacter> Player;
};
