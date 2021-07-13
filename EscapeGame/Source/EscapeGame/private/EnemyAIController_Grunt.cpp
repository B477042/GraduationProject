// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController_Grunt.h"
#include "DT_DataStruct.h"




AEnemyAIController_Grunt::AEnemyAIController_Grunt()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_GruntBoard.BB_GruntBoard'"));
	if (BB.Succeeded())
	{
		BBData = BB.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("BehaviorTree'/Game/MyFolder/AIData/BT_GruntEnemyTree.BT_GruntEnemyTree'"));
	if (BT.Succeeded())
	{
		BTData = BT.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_GRUNT(TEXT("DataTable'/Game/MyFolder/DataTable/DT_GruntType.DT_GruntType'"));
	if (DT_GRUNT.Succeeded())
	{
		DT_Grunt = DT_GRUNT.Object;
	}

}

const UDataTable * AEnemyAIController_Grunt::GetDT_Grunt()
{
	return DT_Grunt;
}

void AEnemyAIController_Grunt::BeginPlay()
{
	Super::BeginPlay();
	RunAI();
}

void AEnemyAIController_Grunt::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemyAIController_Grunt::RunAI()
{
	Super::RunAI();
	
	
}

void AEnemyAIController_Grunt::StopAI()
{
	Super::StopAI();
}
