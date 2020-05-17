// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Dash_To.generated.h"

/**
 * �پ�� �غ� �մϴ�.
 * ������ Charactor movement�� max speed �÷��ݴϴ�
 */
UCLASS()
class ESCAPEGAME_API UBTTask_Dash_To : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Dash_To();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
