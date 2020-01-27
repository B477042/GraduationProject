// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"


/**
 *
	AI가 Player를 스캔하는 Task다. 
	여러가지를 스캔해서 그 중에서 PlayerCharacter를 골라낸다
	발견한 Player는 저장한다

 */
UCLASS()
class ESCAPEGAME_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_Detect();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory, float DeltaSeconds)override;

};
