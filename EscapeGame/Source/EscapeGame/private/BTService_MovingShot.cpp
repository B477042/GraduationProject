// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_MovingShot.h"

#include "AIController.h"
#include "Actor/Character/EnemyCharacter_Gunner.h"

UBTService_MovingShot::UBTService_MovingShot()
{
	NodeName = TEXT("Gunner Moving Shoot");
	Interval = 0.05f;
	RandomDeviation = 0.0f;
	
}


void UBTService_MovingShot::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	auto AIController = OwnerComp.GetAIOwner();

	auto OwnerChara = Cast <AEnemyCharacter_Gunner>(AIController->GetPawn());
	if (!OwnerChara) { UE_LOG(LogTemp, Error, TEXT("Warnning : %s is not Gunner Type Character"), *AIController->GetPawn()->GetName()); return; }

	

	OwnerChara->Attack();


}