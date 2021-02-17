// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGunnerAIController.h"

AEnemyGunnerAIController::AEnemyGunnerAIController()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB_Data(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_GunnerBoard.BB_GunnerBoard'"));
	if (BB_Data.Succeeded())
	{
		BBData = BB_Data.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT_DATA(TEXT("BehaviorTree'/Game/MyFolder/AIData/BT_GunnerTree.BT_GunnerTree'"));
	if (BT_DATA.Succeeded())
	{
		BTData = BT_DATA.Object;
	}


}
void AEnemyGunnerAIController::BeginPlay()
{
	Super::BeginPlay();
	RunAI();
}

void AEnemyGunnerAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AEnemyGunnerAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyGunnerAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyGunnerAIController::RunAI()
{
	Super::RunAI();
}

void AEnemyGunnerAIController::StopAI()
{
	Super::StopAI();
}