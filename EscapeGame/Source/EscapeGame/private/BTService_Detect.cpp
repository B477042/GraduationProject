// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "EGPlayerCharacter.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Try Scanning Player as Target");
	Interval = 1.0f;
	// Scan 7m - > default
	DetectRadius = 700.0f;
	bIsDebugMode = true;

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


	
	
	//탐지된 여러가지의 결과들
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	

	//PlayerCharacter를 Overlap 반응으로 찾아낸다. 모양은 DetectRadius만한 구
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

	

	if (bResult)
	{
		
		for (auto OverlapResult : OverlapResults)
		{
			//스캔한 결과들 중에서 PlayerCharacter를 찾아낸다
			//찾았다면 찾았다고 표시한다===1단계
			auto resultChara = Cast<AEGPlayerCharacter>(OverlapResult.Actor);
			if (resultChara == nullptr)continue;

			if (resultChara->GetController()->IsPlayerController())
			{
				//Debug 모드라면 그려서 표시해준다
				if (bIsDebugMode)
				{
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Purple, false, 0.2f);
				//Draw Point Detected Player
				DrawDebugPoint(World, resultChara->GetTargetLocation(), 100.0f, FColor::Red, false, 0.2f);
				
				FVector DebugFVPoint = ControllingPawn->GetActorLocation() + ControllingPawn->GetActorForwardVector()/**FVector(1.0f,1.0f,1.0f)*/*600.0f;
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), DebugFVPoint, FColor::Red, false, 2.0f);
				}
				

				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer,resultChara);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPos, resultChara->GetActorLocation());
				EGLOG(Warning,TEXT("Detect : %s") , *OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetPlayer)->GetName());
				return;
			}
			
			
		}
	}

	else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
				
		}
	//draw detect range
	if (bIsDebugMode)
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Yellow, false, 0.2f);


	//OwnerComp.GetBlackboardComponent()->Getvalue
}

