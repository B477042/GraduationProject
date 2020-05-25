// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Thunderbolt.h"
#include "EnemyBossCharacter.h"
#include "EnemyAIController.h"
UBTTaskNode_Thunderbolt::UBTTaskNode_Thunderbolt()
{
	NodeName = TEXT("Thunderbolt");
}

EBTNodeResult::Type UBTTaskNode_Thunderbolt::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Chara = Cast<AEnemyBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto AiCon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!Chara || !AiCon) {
		EGLOG(Warning, TEXT("That's not EnemyChara"));
		return EBTNodeResult::Failed;
	}

	Chara->Thunderbolt();


	return EBTNodeResult::Succeeded;
}
