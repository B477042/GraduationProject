// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"


/**
 *
	Ai will scan Player
	


 */
UCLASS()
class ESCAPEGAME_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_Detect();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory, float DeltaSeconds)override;

private:
	//AActor* FindNearest(const TArray<FOverlapResult>& Results);
};
