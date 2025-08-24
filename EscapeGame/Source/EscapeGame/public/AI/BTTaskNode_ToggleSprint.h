// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ToggleSprint.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UBTTaskNode_ToggleSprint : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_ToggleSprint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)override;
	UPROPERTY(BlueprintReadOnly, Category = "Info")
		bool bIsToggled;
};
