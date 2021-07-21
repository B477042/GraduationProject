// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_MeasureDistance.generated.h"

/**
 * 
 */
UCLASS(meta = (ToolTip = "Measure the distance between yourself and the target. Returns true if the measurement is farther than Standard Distanc"))
class ESCAPEGAME_API UBTDecorator_MeasureDistance : public UBTDecorator
{
	GENERATED_BODY()
		
public:
	UBTDecorator_MeasureDistance();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Variable", meta = (ToolTip = "Return true if shorter than this value"))
		float StandardDistance;
	
	const FName TARGETPLAYER = "TargetPlayer";
	
};
