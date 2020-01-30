// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "EGPlayerCharacter.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("MyDetect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)return;
	//EGLOG(Warning, TEXT("Owner Chara : %s"), *ControllingPawn->GetName());

	auto Center = ControllingPawn->GetActorLocation();

	auto World = GetWorld();
	if (World == nullptr)return;
	// Scan 7m
	float DetectRadius = 700.0f;

	//EGLOG(Warning, TEXT("Owner Comp Name : %s"), *OwnerComp.GetName()); //=> BTComponent 
	//EGLOG(Warning, TEXT("Owner Comp -> Owner : %s"), *OwnerComp.GetOwner()->GetName()); // => EnemyAIController(First Controller)


	
	/*auto OwnerChara = Cast<ACharacter>*/
	
	
	
	
	//Ž���� ���������� �����
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	

	//PlayerCharacter�� Overlap �������� ã�Ƴ���. ����� DetectRadius���� ��
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

	
	//draw detect range
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Yellow, false, 0.2f);
	if (bResult)
	{
		
		for (auto OverlapResult : OverlapResults)
		{
			//��ĵ�� ����� �߿��� PlayerCharacter�� ã�Ƴ���
			//ã�Ҵٸ� ã�Ҵٰ� ǥ���Ѵ�===1�ܰ�
			auto resultChara = Cast<AEGPlayerCharacter>(OverlapResult.Actor);
			if (resultChara == nullptr)continue;

			if (resultChara->GetController()->IsPlayerController())
			{
				EGLOG(Warning, TEXT("Detect!"));
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Purple, false, 0.2f);
				//Draw Point Detected Player
				DrawDebugPoint(World, resultChara->GetTargetLocation(), 100.0f, FColor::Red, false, 0.2f);
			}
			
		/*	else
			{

			}*/
		}
	}
	
}
