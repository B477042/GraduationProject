// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ShootingAttack.generated.h"

/**
 * Grunt Enemy¿ë Task Node
 */
UCLASS()
class ESCAPEGAME_API UBTTask_ShootingAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_ShootingAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
