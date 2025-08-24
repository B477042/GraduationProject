// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Advanced_Detect.generated.h"

/**
 *  BTService Detect�� ���������� 
 */
UCLASS()
class ESCAPEGAME_API UBTService_Advanced_Detect : public UBTService
{
	GENERATED_BODY()
public:

	UBTService_Advanced_Detect();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory, float DeltaSeconds)override;
	//�ڽ��� �������̴�
	FVector DetectBoxSize;
};
