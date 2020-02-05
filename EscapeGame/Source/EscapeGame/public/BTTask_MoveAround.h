// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveAround.generated.h"

/**
 * Move Actor  To Random Pos.
 * 
 */
UCLASS()
class ESCAPEGAME_API UBTTask_MoveAround : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_MoveAround();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
