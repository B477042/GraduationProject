// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Dash_To.h"
#include "EnemyAIController.h"
#include "EnemyBossCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_Dash_To::UBTTask_Dash_To()
{
	NodeName = TEXT("Set Dash State");
}

EBTNodeResult::Type UBTTask_Dash_To::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto OwnerChara = Cast<AEnemyBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!OwnerChara)
	{
		EGLOG(Warning, TEXT("Who is Owner"));
		return EBTNodeResult::Failed;
	}

	OwnerChara->GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	OwnerChara->SetState(EBossState::Dash);


	return EBTNodeResult::Succeeded;
}