// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "..\public\EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DT_DataStruct.h"




const FName AEnemyAIController::TargetPlayer(TEXT("TargetPlayer"));
const FName AEnemyAIController::HomePos(TEXT("HomePos"));
const FName AEnemyAIController::PatrolPos(TEXT("PatrolPos"));

AEnemyAIController::AEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_GRUNT(TEXT("DataTable'/Game/MyFolder/DataTable/DT_GruntType.DT_GruntType'"));
	if (DT_GRUNT.Succeeded())
	{
		DT_Grunt = DT_GRUNT.Object;
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

const UDataTable * AEnemyAIController::GetDT_Grunt()
{
	return DT_Grunt;
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
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
