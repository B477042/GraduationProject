// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController_Boss.h"


//FName AEnemyAIController_Boss::Name_TargetPos = TEXT("TargetPos");
FName AEnemyAIController_Boss::ActionTimer = TEXT("ActionTimer");
FName AEnemyAIController_Boss::IsDash = TEXT("IsDash?");
FName AEnemyAIController_Boss::MP = TEXT("MP");
FName AEnemyAIController_Boss::BackStepPoint = TEXT("BackStepPoint");
FName AEnemyAIController_Boss::SoundPlayed = TEXT("SoundPlayed");
FName AEnemyAIController_Boss::BehaviorPattern = TEXT("BehaviorPattern");

AEnemyAIController_Boss::AEnemyAIController_Boss()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB_Data(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_BossBoard.BB_BossBoard'"));
	if (BB_Data.Succeeded())
	{
		BBData = BB_Data.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT_DATA(TEXT("BehaviorTree'/Game/MyFolder/AIData/BT_BossTree.BT_BossTree'"));
	if (BT_DATA.Succeeded())
	{
		BTData = BT_DATA.Object;
	}

	bIsDebugMode = true;
	n_DetectRange = 1000.0f;
}

void AEnemyAIController_Boss::BeginPlay()
{
	Super::BeginPlay();

	RunAI();

}

void AEnemyAIController_Boss::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemyAIController_Boss::RunAI()
{
	Super::RunAI();

}

void AEnemyAIController_Boss::StopAI()
{
	Super::StopAI();
}

//Boss Character에서 호출
void AEnemyAIController_Boss::SaveGame(FBossData& BossData)
{
	/*if (!SaveInstance)
		return;

	FBossData& BossData = SaveInstance->BossData;*/
/*	SaveInstance->*/BossData.ActionTimer = GetBlackboardComponent()->GetValueAsFloat(ActionTimer);
/*	SaveInstance->*/BossData.MP = GetBlackboardComponent()->GetValueAsFloat(MP);
/*	SaveInstance->*/BossData.bIsDash = GetBlackboardComponent()->GetValueAsBool(IsDash);
/*	SaveInstance->*/BossData.bSoundPlayed = GetBlackboardComponent()->GetValueAsBool(SoundPlayed);
/*	SaveInstance->*/BossData.BackStepPoint = GetBlackboardComponent()->GetValueAsVector(BackStepPoint);
/*	SaveInstance->*/BossData.BehaviorPattern = GetBlackboardComponent()->GetValueAsEnum(BehaviorPattern);
	EGLOG(Error, TEXT("Boss Save Complete MP : %f"), GetBlackboardComponent()->GetValueAsFloat(MP));

}
//에서 호출
void AEnemyAIController_Boss::LoadGame(const FBossData& BossData)
{
	/*if (!LoadInstance)
		return;*/
	EGLOG(Error, TEXT("Load instance data mp : %f"), /*LoadInstance->*/BossData.MP);
	GetBlackboardComponent()->SetValueAsFloat(ActionTimer,/*LoadInstance->*/BossData.ActionTimer );
	GetBlackboardComponent()->SetValueAsFloat(MP, /*LoadInstance->*/BossData.MP);
	GetBlackboardComponent()->SetValueAsBool(IsDash, /*LoadInstance->*/BossData.bIsDash);
	GetBlackboardComponent()->SetValueAsBool(SoundPlayed, /*LoadInstance->*/BossData.bSoundPlayed);
	GetBlackboardComponent()->SetValueAsVector(BackStepPoint, /*LoadInstance->*/ BossData.BackStepPoint);
	GetBlackboardComponent()->SetValueAsEnum(BehaviorPattern, /*LoadInstance->*/BossData.BehaviorPattern);
	EGLOG(Error, TEXT("Boss Load Complete MP : %f"),GetBlackboardComponent()->GetValueAsFloat(MP));
}
