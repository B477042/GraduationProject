// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Boss_DashATK.h"

#include "AIController.h"
#include "Actor/Character/EnemyBossCharacter.h"

UBTTask_Boss_DashATK::UBTTask_Boss_DashATK()
{
	NodeName = TEXT("Throw Fire Ball");
}

EBTNodeResult::Type UBTTask_Boss_DashATK::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto OwnerChara = Cast<AEnemyBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!OwnerChara) {
		EGLOG(Error, TEXT("Not Boss Character"));
		return EBTNodeResult::Failed;
	}


	OwnerChara->ThrowFireBall();

	return EBTNodeResult::Succeeded;
}
