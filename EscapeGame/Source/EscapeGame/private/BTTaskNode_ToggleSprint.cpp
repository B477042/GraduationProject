// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_ToggleSprint.h"
#include "EnemyCharacter_Gunner.h"
#include "AIController.h"
#include "AnimInstance_Gunner.h"

UBTTaskNode_ToggleSprint::UBTTaskNode_ToggleSprint()
{
	NodeName = TEXT("Toggle Gunner Sprint");

	bIsToggled = false;
}


EBTNodeResult::Type UBTTaskNode_ToggleSprint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto Character = Cast<AEnemyCharacter_Gunner>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character) { UE_LOG(LogTemp, Error, TEXT("CASTING FAIL!!!!")); return  EBTNodeResult::Failed; }
	auto Anim = Cast<UAnimInstance_Gunner>(Character->GetMesh()->GetAnimInstance());


	if (bIsToggled)bIsToggled = false;
	else bIsToggled = true;

	Anim->SetAccelerating(bIsToggled);

	return EBTNodeResult::Succeeded;
}