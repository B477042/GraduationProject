// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Boss.h"

FName AAIController_Boss::TargetPos = TEXT("TargetPos");
FName AAIController_Boss::ActionTimer = TEXT("ActionTimer");
FName AAIController_Boss::IsDash = TEXT("IsDash?");


AAIController_Boss::AAIController_Boss()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB_Data(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_BossBoard.BB_BossBoard'"));
	if (BB_Data.Succeeded())
	{
		BBData = BB_Data.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT_DATA(TEXT("BehaviorTree'/Game/MyFolder/AIData/BT_BossTree.BT_BossTree'"));
	if (BT_DATA.Succeeded())
	{
		BTData = BT_DATA.Object;
	}

	bIsDebugMode = true;
	n_DetectRange = 1000.0f;
}

void AAIController_Boss::BeginPlay()
{
	Super::BeginPlay();

	RunAI();

}

void AAIController_Boss::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAIController_Boss::RunAI()
{
	Super::RunAI();
	if (UseBlackboard(BBData, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePos, GetPawn()->GetActorLocation());
	}
}

void AAIController_Boss::StopAI()
{
	Super::StopAI();
}
