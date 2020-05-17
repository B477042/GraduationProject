// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "BTDecorator_Boss_IsDashing.generated.h"

/**
 * Return true. If Boss' state is Dash
 */
UCLASS()
class ESCAPEGAME_API UBTDecorator_Boss_IsDashing : public UBTDecorator_Blackboard
{
	GENERATED_BODY()
public:
	UBTDecorator_Boss_IsDashing();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
