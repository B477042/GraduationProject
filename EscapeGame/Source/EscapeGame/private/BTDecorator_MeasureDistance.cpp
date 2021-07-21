// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_MeasureDistance.h"
#include "EnemyAIController_Grunt.h"

UBTDecorator_MeasureDistance::UBTDecorator_MeasureDistance()
{
	NodeName = TEXT("Measure Distance To Target");
	
	StandardDistance = 400.0f;
}

bool UBTDecorator_MeasureDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Controller = OwnerComp.GetAIOwner();
	auto BB = Controller->GetBlackboardComponent();
	if(!BB)
	{
		UE_LOG(LogTemp, Warning, TEXT("Decorator Casting Failed"));
		return false;
	}
	auto TargetActor = Cast<AActor>(BB->GetValueAsObject(TARGETPLAYER));
	
	
	//Target Pos Vector Value
	const FVector TargetPos = TargetActor->GetActorLocation();
	const FVector OwnerPos = Controller->GetPawn()->GetActorLocation();

	const float ResultDist = FVector::Distance(TargetPos, OwnerPos);

	EGLOG(Warning, TEXT("Measure Distance : %f"), ResultDist);
	
	if(ResultDist > StandardDistance)
	{
		EGLOG(Log, TEXT("Too Far"));
		return true;
		
	}
	else
	{
		EGLOG(Log, TEXT("Too Close"));
		return false;
	}
	
}
