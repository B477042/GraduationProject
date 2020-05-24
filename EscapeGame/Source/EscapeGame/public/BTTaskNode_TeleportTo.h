// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_TeleportTo.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UBTTaskNode_TeleportTo : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_TeleportTo();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	//적의 위치가 셋팅된 상태라면 실행시켜준다. 
	FVector CalcTeleportPos(const FVector& TargetPos);
	//얼마나 텔레포트 할지 길이
	float TeleportDistance;
	bool CanTeleportThere(const FVector & TeleportPos);


};
