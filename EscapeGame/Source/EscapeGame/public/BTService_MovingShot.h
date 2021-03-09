// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_MovingShot.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UBTService_MovingShot : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_MovingShot();

	virtual void TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)override;
};
