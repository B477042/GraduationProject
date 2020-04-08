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
	Idle=0, Talking1=1, Talking2=2, Talking3=3
};

UCLASS()
class ESCAPEGAME_API UAnim_DrJoe : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_DrJoe();

	
	UFUNCTION(BlueprintCallable, Category = "Custom")
		UAnimSequence* PosePlay(UAnimSequence* input);
private:
	UFUNCTION(BlueprintCallable, Category = "Custom")
		void randState();

	
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	EState State;

	//���� �ð����� ��� �ٲ� �� �� Ÿ�̸�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
		float PoseTimer;
	//Ÿ�̸��� ����Ʈ. �̸�ŭ ����Ǹ� ���½�Ų��
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
		float LimitTimer;
};
