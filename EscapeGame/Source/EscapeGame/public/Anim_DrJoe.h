// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Animation/AnimInstance.h"
#include "Anim_DrJoe.generated.h"

/**
 *		Dr 캐릭터의 anim bp에 사용될 클래스
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

	//일정 시간마다 포즈를 바꿀 때 쓸 타이머
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
		float PoseTimer;
	//타이머의 리미트. 이만큼 진행되면 리셋시킨다
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
		float LimitTimer;
};
