// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Advanced_Detect.h"

#include "AIController.h"
#include "Actor/Character/EGPlayerCharacter.h"
#include "Actor/Character/EnemyBossCharacter.h"
#include "Actor/Character/EnemyCharacter.h"
#include "Actor/Controller/EnemyAIController_Boss.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_Advanced_Detect::UBTService_Advanced_Detect()
{
	NodeName = TEXT("Search Palyer using Box ");

	DetectBoxSize = FVector(1000.0f,1000.0f, 500.0f);

}

void UBTService_Advanced_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	auto ControllingPawn = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)return;
	

	auto Center = ControllingPawn->GetActorLocation();
	Center.Z += DetectBoxSize.Z;

	auto World = GetWorld();
	if (World == nullptr)return;

	//Ž���� ���������� �����
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

	//PlayerCharacter�� Overlap �������� ã�Ƴ���. ����� �ڽ������� Center�� Controlling pawn�� �Ӹ� ��ġ���̴�
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeBox(DetectBoxSize), CollisionQueryParam);


	if (bResult)
	{

		for (FOverlapResult&  OverlapResult : OverlapResults)
		{
			//��ĵ�� ����� �߿��� PlayerCharacter�� ã�Ƴ���
			//ã�Ҵٸ� ã�Ҵٰ� ǥ���Ѵ�===1�ܰ�
			TObjectPtr<AEGPlayerCharacter> resultChara = Cast<AEGPlayerCharacter>(OverlapResult.GetActor());
			if (!resultChara)
			{
				continue;
			}

			if (resultChara->GetController()->IsPlayerController())
			{
				////Debug ����� �׷��� ǥ�����ش�
				//if (DrawingDebugMode)
				//{
				//	DrawDebugBox(World, Center, DetectBoxSize, FColor::Purple, false, 0.2f);

				//	//DrawDebugBox(World, Center, DetectBoxSize, 16, FColor::Purple, false, 0.2f);
				//	//Draw Point Detected Player
				//	//Ž���� �÷��̾� ���� ǥ���ϱ�
				//	DrawDebugPoint(World, resultChara->GetTargetPlayerLocation(), 100.0f, FColor::Magenta, false, 0.2f);

				//	FVector DebugFVPoint = ControllingPawn->GetActorLocation() + ControllingPawn->GetActorForwardVector()/**FVector(1.0f,1.0f,1.0f)*/*600.0f;
				//	DrawDebugLine(World, ControllingPawn->GetActorLocation(), DebugFVPoint, FColor::Red, false, 2.0f);
				//}


				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, resultChara);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController_Boss::TargetPos, resultChara->GetActorLocation());
				//OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPos, resultChara->GetActorLocation());
				//EGLOG(Warning, TEXT("Detect : %s"), *OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetPlayer)->GetName());
				return;
			}


		}
	}

	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController_Boss::IsDash, false);
	auto temp = Cast<AEnemyBossCharacter>(ControllingPawn);
	if (temp)
	{
	temp->SetState(EBossState::Walk);
	temp->GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	}
	

	////draw detect range
	//if (DrawingDebugMode)
	//	DrawDebugBox(World, Center, DetectBoxSize, FColor::Yellow, false, 0.4f);


}
