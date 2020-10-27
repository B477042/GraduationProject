// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "..\public\EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"





const FName AEnemyAIController::TargetPlayer(TEXT("TargetPlayer"));
const FName AEnemyAIController::HomePos(TEXT("HomePos"));
const FName AEnemyAIController::PatrolPos(TEXT("PatrolPos"));

AEnemyAIController::AEnemyAIController()
{
	
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



void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	//RunAI();
}

void AEnemyAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemyAIController::RunAI()
{
	
	RunBehaviorTree(BTData);
	EGLOG(Warning, TEXT("Running"));
}

void AEnemyAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		EGLOG(Warning, TEXT("PLz stop"));
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
		return;
	}

	EGLOG(Warning, TEXT("You Fucking racist"));

}
