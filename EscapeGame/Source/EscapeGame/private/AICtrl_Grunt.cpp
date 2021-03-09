// Fill out your copyright notice in the Description page of Project Settings.


#include "AICtrl_Grunt.h"
#include "DT_DataStruct.h"




AAICtrl_Grunt::AAICtrl_Grunt()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_EnemyBoard.BB_EnemyBoard'"));
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

const UDataTable * AAICtrl_Grunt::GetDT_Grunt()
{
	return DT_Grunt;
}

void AAICtrl_Grunt::BeginPlay()
{
	Super::BeginPlay();
	RunAI();
}

void AAICtrl_Grunt::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAICtrl_Grunt::RunAI()
{
	Super::RunAI();
	
	
}

void AAICtrl_Grunt::StopAI()
{
	Super::StopAI();
}
