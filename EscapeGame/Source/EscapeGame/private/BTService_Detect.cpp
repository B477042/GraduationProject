// Fill out your copyright notice in the Description page of Project Settings.



//#include "DrawDebugHelpers.h"
#include "AI/BTService_Detect.h"

#include "AIController.h"
#include "Actor/Character/EGPlayerCharacter.h"
#include "Actor/Controller/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Try Scanning Player as Target");
	Interval = 0.5f;
	// Scan 7m - > default
	DetectRadius = 700.0f;
	//bIsDebugMode = true;
	

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


	
	
	//Ž���� ���������� �����
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	

	//PlayerCharacter�� Overlap �������� ã�Ƴ���. ����� DetectRadius���� ��
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

	

	if (bResult)
	{
		
		for (auto OverlapResult : OverlapResults)
		{
			//��ĵ�� ����� �߿��� PlayerCharacter�� ã�Ƴ���
			//ã�Ҵٸ� ã�Ҵٰ� ǥ���Ѵ�===1�ܰ�
			auto resultChara = Cast<AEGPlayerCharacter>(OverlapResult.GetActor());
			if (!resultChara)continue;

			if (resultChara->GetController()->IsPlayerController())
			{
				////Debug ����� �׷��� ǥ�����ش�
				//if (DrawingDebugMode)
				//{
				//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Purple, false, 0.2f);
				////Draw Point Detected Player
				//DrawDebugPoint(World, resultChara->GetTargetPlayerLocation(), 100.0f, FColor::Red, false, 0.2f);
				//
				//FVector DebugFVPoint = ControllingPawn->GetActorLocation() + ControllingPawn->GetActorForwardVector()/**FVector(1.0f,1.0f,1.0f)*/*600.0f;
				//DrawDebugLine(World, ControllingPawn->GetActorLocation(), DebugFVPoint, FColor::Red, false, 2.0f);
				//}
				//

				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer,resultChara);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPos, resultChara->GetActorLocation());
				//EGLOG(Warning,TEXT("Detect : %s") , *OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetPlayer)->GetName());
				return;
			}
			
			
		}
	}

	else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
				
		}
	//draw detect range
	//if (DrawingDebugMode)
	//	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Yellow, false, 0.2f);


	//OwnerComp.GetBlackboardComponent()->Getvalue
}

