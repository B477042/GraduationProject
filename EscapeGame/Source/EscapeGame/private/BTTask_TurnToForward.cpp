// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TurnToForward.h"

#include "AIController.h"
#include "Actor/Character/EnemyCharacter.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

EBTNodeResult::Type UBTTask_TurnToForward::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//Owner Chara of this node. if Not a Enemy Chara return failed
	auto ControllingChara = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingChara == nullptr)return EBTNodeResult::Failed;

	FVector FV = ControllingChara->GetActorForwardVector();
	FV.Z = 0.0f;
	FRotator ForwardRot = FRotationMatrix::MakeFromX(FV).Rotator();
	ControllingChara->SetActorRotation(FMath::RInterpTo(ControllingChara->GetActorRotation(), ForwardRot, GetWorld()->GetDeltaSeconds(), 2.0f));
	

	return EBTNodeResult::Succeeded;
}
