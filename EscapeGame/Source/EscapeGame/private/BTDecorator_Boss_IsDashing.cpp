// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Boss_IsDashing.h"

#include"EnemyBossCharacter.h"
#include"EnemyAIController_Boss.h"

UBTDecorator_Boss_IsDashing::UBTDecorator_Boss_IsDashing()
{
	NodeName = TEXT("Is Boss Not Dashing?");
}

bool UBTDecorator_Boss_IsDashing::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Boss = Cast<AEnemyBossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Boss)
	{
		EGLOG(Error, TEXT("It's Not Boss Chara. "));
		return false;
	}

	auto Blackboard = OwnerComp.GetBlackboardComponent();


	if (Boss->GetState() == EBossState::Walk)
	{
		Blackboard->SetValueAsBool(AEnemyAIController_Boss::IsDash, false);
		return true;
	}
	Blackboard->SetValueAsBool(AEnemyAIController_Boss::IsDash, true);
	 return false;




}