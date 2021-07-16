// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShootingAttack.h"
#include "EnemyAIController_Grunt.h"
#include "GruntCharacter.h"
UBTTask_ShootingAttack::UBTTask_ShootingAttack()
{
	NodeName = TEXT("Shooting Attack For Grunt");
	
}

EBTNodeResult::Type UBTTask_ShootingAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<AEnemyAIController_Grunt>(OwnerComp.GetAIOwner());
	if(!Controller)
	{
		EGLOG(Error, TEXT("OwnerComp is not Grunt Controller"));
		return EBTNodeResult::Failed;
	}

	auto Character = Cast<AGruntCharacter>(Controller->GetPawn());
	if(!Character)
	{
		EGLOG(Error, TEXT("Cast Failed"));
		return EBTNodeResult::Failed;
	}

	Character->FireAttack();
	
	return EBTNodeResult::Succeeded;
}
