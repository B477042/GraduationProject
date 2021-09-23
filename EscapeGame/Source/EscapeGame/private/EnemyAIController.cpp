// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"




const FName AEnemyAIController::TargetPlayer(TEXT("TargetPlayer"));
const FName AEnemyAIController::HomePos(TEXT("HomePos"));
const FName AEnemyAIController::PatrolPos(TEXT("PatrolPos"));
const FName AEnemyAIController::TargetPos(TEXT("TargetPos"));
AEnemyAIController::AEnemyAIController()
{
	
}

void AEnemyAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	//EGLOG(Warning, TEXT("AIController Online : %s"), *InPawn->GetName());

	AEnemyCharacter const* TempCharacter = Cast<AEnemyCharacter>(InPawn);
	if (!TempCharacter)
	{
		EGLOG(Error, TEXT("Casting Failed"));
		return;
	}
	//Bind Function
	TempCharacter->OnTakeDamaged.CreateLambda([this](AActor* OtherActor)->void {
		auto ResultActor = GetBlackboardComponent()->GetValueAsObject(TargetPlayer);
		if(!ResultActor)
		{ 
			GetBlackboardComponent()->SetValueAsObject(TargetPlayer, OtherActor);
			return;
		}
		
		});

}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}



void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	//RunAI();
}

void AEnemyAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemyAIController::perceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
}

void AEnemyAIController::RunAI()
{
	if (BBData == nullptr) { EGLOG(Error, TEXT("BBDataError")) return; }
	//if(Blackboard)

	if (UseBlackboard(BBData, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePos, GetPawn()->GetActorLocation());
	}

	RunBehaviorTree(BTData);
//	EGLOG(Warning, TEXT("Running"));
}

void AEnemyAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
		return;
	}

	

}

bool AEnemyAIController::GetTargetLocation(FVector& Retval)
{
	
	const auto Actor = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetPlayer));
	if (!Actor)
	{
		EGLOG(Error, TEXT("Can't find target"));
		return false;
	}
	Retval = Actor->GetActorLocation();
	return true;
}
