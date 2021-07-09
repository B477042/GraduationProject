// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CharacterAnimInstance.h"
#include "Anim_Grunt.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE(FOnFireAttack);

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
		void Notify_FireStart();
	
	UFUNCTION()
	void PlayDeadAnim();
	
	FOnFireAttack OnFireAttack;

protected:
	

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bIsDead;

 
};
