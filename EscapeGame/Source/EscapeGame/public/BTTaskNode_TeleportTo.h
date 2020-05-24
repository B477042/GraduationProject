// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_TeleportTo.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API UBTTaskNode_TeleportTo : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_TeleportTo();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	//���� ��ġ�� ���õ� ���¶�� ��������ش�. 
	FVector CalcTeleportPos(const FVector& TargetPos);
	//�󸶳� �ڷ���Ʈ ���� ����
	float TeleportDistance;
	bool CanTeleportThere(const FVector & TeleportPos);


};
