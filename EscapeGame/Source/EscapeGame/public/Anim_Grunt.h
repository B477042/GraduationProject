// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CharacterAnimInstance.h"
#include "Anim_Grunt.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UAnim_Grunt : public UCharacterAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_Grunt();
	virtual void JumpToComboAttackSection(int32 NewSection);
	virtual void PlayAirattackMontage();

protected:
	
private:

};
