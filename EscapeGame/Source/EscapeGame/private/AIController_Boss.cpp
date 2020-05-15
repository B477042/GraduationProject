// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Boss.h"

AAIController_Boss::AAIController_Boss()
{

	/*static ConstructorHelpers::FObjectFinder<UBlackboardData>BB_Data(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_BossBoard.BB_BossBoard'"));
	if (BB_Data.Succeeded())
	{
		BlackBoard = BB_Data.Object;
	}*/


		
}

void AAIController_Boss::BeginPlay()
{
	Super::BeginPlay();

}

void AAIController_Boss::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAIController_Boss::RunAI()
{
	Super::RunAI();

}

void AAIController_Boss::StopAI()
{
	Super::StopAI();
}
