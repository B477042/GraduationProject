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
	//Owner�� ���� ��ĵ�Ѵ� 1���� ����

	//��ĵ�� ������� player���� �˻��ϰ� player���� �������� �ش�
	

}

