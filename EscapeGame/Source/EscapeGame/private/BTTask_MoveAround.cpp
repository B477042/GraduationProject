// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveAround.h"
#include "NavigationSystem.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"


UBTTask_MoveAround::UBTTask_MoveAround()
{
	NodeName = TEXT("MoveAround");
}

EBTNodeResult::Type UBTTask_MoveAround::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	
	
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)return EBTNodeResult::Failed;

	UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if(NaviSys==nullptr)return EBTNodeResult::Failed;


	//EGLOG(Warning, TEXT("AI Controller rotate : %s"), *ControllingPawn->GetController()->GetControlRotation().ToString());

	//Get Vector From Blackboard Value "HomePos" point to Pawn's Current Pos
	FVector StartingPoint = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyAIController::HomePos);
	//Point to Next Pos.
	FNavLocation NextPoint;

	/** Finds random, point in navigable space restricted to Radius around Origin. Resulting location is not tested for reachability from the Origin
	 *	@param ResultLocation Found point is put here
	 *	@param NavData If NavData == NULL then MainNavData is used.
	 *	@return true if any location found, false otherwise */
	//Set NextPoint Value as Random. From Controlling Pawn's Position, Radius 4m. 
	if (NaviSys->GetRandomPointInNavigableRadius(ControllingPawn->GetActorLocation(), 400.0f, NextPoint))
	{
		//if NextValue valid
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPos, NextPoint);
		return EBTNodeResult::Succeeded;

	}

	EGLOG(Warning, TEXT("Faile"));
	return EBTNodeResult::Failed;
}
