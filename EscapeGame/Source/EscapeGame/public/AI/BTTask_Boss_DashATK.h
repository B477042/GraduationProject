// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Boss_DashATK.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UBTTask_Boss_DashATK : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UBTTask_Boss_DashATK();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
