// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "EGPlayerCharacter.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	auto OwnerChara = Cast<AEnemyCharacter>(OwnerComp.GetOwner());
	auto Center = OwnerChara->GetActorLocation();
	auto World = GetWorld();

	if (OwnerChara == nullptr)return;
	if (World == nullptr)return;

	//탐지된 여러가지의 결과들
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, OwnerChara);
	// Scan 7m
	float DetectRadius = 700.0f;

	//PlayerCharacter를 Overlap 반응으로 찾아낸다. 모양은 DetectRadius만한 구
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

	
	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			auto resultChara = Cast<AEGPlayerCharacter>(OverlapResult.Actor);
			if (resultChara->GetController()->IsPlayerController())
			{
				EGLOG(Warning, TEXT("Detect!"));
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Purple, false, 0.2f);
				//Draw Point Detected Player
				DrawDebugPoint(World, resultChara->GetTargetLocation(), 10.0f, FColor::Orange, false, 0.2f);
			}
			
			else
			{

			}
		}
	}
	else
	//if nothing fund
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Cyan, false, 0.2f);
}
