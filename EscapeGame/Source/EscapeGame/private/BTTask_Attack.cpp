// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"

#include "AIController.h"
#include "Actor/Character/EnemyCharacter.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

EBTNodeResult::Type  UBTTask_Attack :: ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingChara = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingChara == nullptr)return EBTNodeResult::Failed;

	ControllingChara->Attack();

	return EBTNodeResult::Succeeded;
}
