// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Grunt.h"
#include "GruntCharacter.h"
#include "EnemyAIController_Grunt.h"
#include "Components/CapsuleComponent.h"

UAnim_Grunt::UAnim_Grunt()
{
	bIsDead = false;



	/*
	 * Load Melee Attack Montage
	 */
	static ConstructorHelpers::FObjectFinder<UAnimMontage>M_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_Grunt_Attack.m_Grunt_Attack'"));
	if (M_ATTACK.Succeeded())
	{
		AttackMontage = M_ATTACK.Object;
		
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>ANIM_Fire(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/Montage_Grunt_Fire.Montage_Grunt_Fire'"));
	if(ANIM_Fire.Succeeded())
	{
		FireAttackMontage = ANIM_Fire.Object;
	}


	
}

void UAnim_Grunt::JumpToComboAttackSection(int32 NewSection)
{

}

void UAnim_Grunt::PlayAttackMontage()
{
	Super::PlayAttackMontage();
	

}

void UAnim_Grunt::AnimNotify_Notify_CheckRange()
{
	
	//Excute Delegate 
	AttackEvent_Delegate.Broadcast();
	

}

void UAnim_Grunt::AnimNotify_Notify_FireStart()
{
	OnFireAttack.Execute();
}

void UAnim_Grunt::AnimNotify_AnimNotify_DeadStart()
{
	 AGruntCharacter* const OwnerChara = Cast<AGruntCharacter>(GetOwningActor());
	if (!OwnerChara)
	{
		EGLOG(Error, TEXT("Casting Failed"));
		return;
	}

	AEnemyAIController_Grunt* const AICon = Cast<AEnemyAIController_Grunt>(OwnerChara->GetController());
	if (!AICon)
	{
		EGLOG(Error, TEXT("Casting Failed"));
		return;
	}

	OwnerChara->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OwnerChara->PlayDeathEffect();
	
	AICon->StopAI();
	
}

void UAnim_Grunt::AnimNotify_AnimNotify_DeadEnd()
{
	if (!GetOwningActor())
	{
		EGLOG(Error, TEXT("Owner is dead"));
		return;
	}
	//GetOwningActor()->Destroy();
	auto OwnerActor = GetOwningActor();
	if (!OwnerActor)
	{
		EGLOG(Error, TEXT("Owing Actor is nullptr"));
		return;
	}
	OwnerActor->Destroy();

}

void UAnim_Grunt::PlayDeadAnim()
{
	bIsDead = true;
	StopAllMontages(0);
}

UAnimMontage* UAnim_Grunt::GetFireAttackMontage()
{
	return FireAttackMontage;
}

