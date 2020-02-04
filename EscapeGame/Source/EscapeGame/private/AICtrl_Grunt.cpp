// Fill out your copyright notice in the Description page of Project Settings.


#include "AICtrl_Grunt.h"



const FName AAICtrl_Grunt::TargetPlayer(TEXT("TargetPlayer"));
const FName AAICtrl_Grunt::HomePos(TEXT("HomePos"));
const FName AAICtrl_Grunt::PatrolPos(TEXT("PatrolPos"));

AAICtrl_Grunt::AAICtrl_Grunt()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_EnemyBoard.BB_EnemyBoard'"));
	if (BB.Succeeded())
	{
		BBData = BB.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("BehaviorTree'/Game/MyFolder/AIData/BT_GruntEnemyTree.BT_GruntEnemyTree'"));
	if (BT.Succeeded())
	{
		BTData = BT.Object;
	}

}