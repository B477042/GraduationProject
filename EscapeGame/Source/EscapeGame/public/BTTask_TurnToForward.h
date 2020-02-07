// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TurnToForward.generated.h"

/**
 * Turn Actor To Forward Vector
 */
UCLASS()
class ESCAPEGAME_API UBTTask_TurnToForward : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
