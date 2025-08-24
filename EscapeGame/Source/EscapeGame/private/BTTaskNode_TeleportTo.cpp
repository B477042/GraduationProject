// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_TeleportTo.h"

#include "AIController.h"
#include "Actor/Character/EnemyCharacter.h"
#include "Actor/Controller/EnemyAIController.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskNode_TeleportTo::UBTTaskNode_TeleportTo()
{
	NodeName = TEXT("Teleport To ");
	TeleportDistance = 1000.0f;
}

EBTNodeResult::Type UBTTaskNode_TeleportTo::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Chara = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto AiCon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (!Chara ||!AiCon) { 
		EGLOG(Warning, TEXT("That's not EnemyChara"));
		return EBTNodeResult::Failed;
	}

	auto newPos = CalcTeleportPos(AiCon->GetBlackboardComponent()->GetValueAsVector(TEXT("TargetPos")));
	if (CanTeleportThere(newPos,Chara))
	{
		
		Chara->TeleportTo(newPos, FRotator::ZeroRotator);

		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}




FVector UBTTaskNode_TeleportTo::CalcTeleportPos(const FVector & TargetPos)
{
	FVector Result= FVector::ZeroVector;

	auto tempVec =UKismetMathLibrary::RandomUnitVector()*TeleportDistance;

	tempVec.Z = 0.0f;
	EGLOG(Warning, TEXT("Temp Vec : %s "), *tempVec.ToString());

	Result = tempVec+TargetPos;
	EGLOG(Warning, TEXT("Result Vec : %s "), *Result.ToString());


	return Result;
}


//Line Trace�� �ٴ��� �ִ��� �˻��Ѵ�. �ٴ��� ������ �װ��� ���� ���� ���̴�.
bool UBTTaskNode_TeleportTo::CanTeleportThere(const FVector & TeleportPos, const AActor* IgnoreActor)
{
	if (!IgnoreActor)return false;

	FHitResult hitResult;
	//FHitResult hitResult;
	FCollisionQueryParams param(NAME_None, false, IgnoreActor);
	
	//FCollisionQueryParams
	bool Result = false;


	//������ 150cm���� ������ ���
	bool bResult = GetWorld()->LineTraceSingleByChannel(hitResult, TeleportPos, TeleportPos - FVector(0.0f,0.0f,500.0f),
		//All Block Trace
		ECollisionChannel::ECC_GameTraceChannel2);
	//EdgePos = myTargetVec;
	if (bResult) {
		EGLOG(Warning, TEXT("hit"));
		Result = true; 
	}
	EGLOG(Error, TEXT("Nothing"));


	return Result;
}
