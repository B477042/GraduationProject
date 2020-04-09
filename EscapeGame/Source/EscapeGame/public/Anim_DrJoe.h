// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Animation/AnimInstance.h"
#include "Anim_DrJoe.generated.h"

/**
 *		Dr ĳ������ anim bp�� ���� Ŭ����
 */


UENUM(BlueprintType)
enum class EState :uint8
{
	Idle, Talking1, Talking2, Talking3
};

UCLASS()
class ESCAPEGAME_API UAnim_DrJoe : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_DrJoe();


	
private:
	
	EState State;
	
};
