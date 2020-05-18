// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Boss_DashATK.h"
#include "AIController_Boss.h"
#include "EnemyBossCharacter.h"
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
