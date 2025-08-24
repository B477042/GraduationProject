// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CharacterAnimInstance.h"
#include "Anim_Grunt.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(FOnFireAttack);

UCLASS()
class ESCAPEGAME_API UAnim_Grunt : public UCharacterAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_Grunt();
	virtual void JumpToComboAttackSection(int32 NewSection);
	virtual void PlayAttackMontage();
	//Check Actor At Front of Owner Actor.
	FAttackEventDelegate AttackEvent_Delegate;

	UFUNCTION()
	void AnimNotify_Notify_CheckRange();
	UFUNCTION()
	void AnimNotify_Notify_FireStart();
	UFUNCTION()
	void AnimNotify_AnimNotify_DeadStart();
	UFUNCTION()
	void AnimNotify_AnimNotify_DeadEnd();
	
	UFUNCTION()
	void PlayDeadAnim();
	
	FOnFireAttack OnFireAttack;
	UAnimMontage* GetFireAttackMontage();
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Montage", meta = (AllowPrivateAccess = true))
		UAnimMontage* FireAttackMontage;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsDead;


	class USoundWave* SFX_Death;
	class UParticleSystem* VFX_Explosion;
 
};
