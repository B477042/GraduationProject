// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Grunt.h"



UAnim_Grunt::UAnim_Grunt()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>M_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_Grunt_Attack.m_Grunt_Attack'"));
	if (M_ATTACK.Succeeded())
	{
		AttackMontage = M_ATTACK.Object;
		EGLOG(Warning, TEXT("G Anim!!!!"));
	}
}

void UAnim_Grunt::JumpToComboAttackSection(int32 NewSection)
{

}

void UAnim_Grunt::PlayAttackMontage()
{
	Super::PlayAttackMontage();
	

	if (!Montage_IsPlaying(AttackMontage))
	{
		EGLOG(Warning, TEXT("Montage i s no tplaying"));
	}
}

void UAnim_Grunt::AnimNotify_CheckRange()
{
	//Excute Delegate 
	AttackEvent_Delegate.Broadcast();
	//Owner의 앞을 스캔한다 1미터 정도

	//스캔한 결과에서 player인지 검사하고 player에게 데미지를 준다
	

}

