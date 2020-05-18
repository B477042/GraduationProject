// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Dash_To.generated.h"

/**
 * 뛰어나갈 준비를 합니다.
 * 오너의 Charactor movement의 max speed 올려줍니다
 */
UCLASS()
class ESCAPEGAME_API UBTTask_Dash_To : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Dash_To();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
