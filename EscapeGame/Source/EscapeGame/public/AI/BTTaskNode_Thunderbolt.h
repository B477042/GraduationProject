// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Thunderbolt.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UBTTaskNode_Thunderbolt : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_Thunderbolt();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
