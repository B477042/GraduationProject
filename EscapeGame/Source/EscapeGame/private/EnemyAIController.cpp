// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "..\public\EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


AEnemyAIController::AEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_EnemyBoard.BB_EnemyBoard'"));
	if (BB.Succeeded())
	{
		BBData = BB.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("BehaviorTree'/Game/MyFolder/AIData/BT_EnemyTree.BT_EnemyTree'"));
	if (BT.Succeeded())
	{
		BTDtat = BT.Object;
	}
}

void AEnemyAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	EGLOG(Warning, TEXT("AIController Online : %s"), *InPawn->GetName());
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
