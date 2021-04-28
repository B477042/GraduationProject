// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Boss.h"
#include "EGSaveGame.h"

//FName AAIController_Boss::Name_TargetPos = TEXT("TargetPos");
FName AAIController_Boss::ActionTimer = TEXT("ActionTimer");
FName AAIController_Boss::IsDash = TEXT("IsDash?");
FName AAIController_Boss::MP = TEXT("MP");
FName AAIController_Boss::BackStepPoint = TEXT("BackStepPoint");
FName AAIController_Boss::SoundPlayed = TEXT("SoundPlayed");
FName AAIController_Boss::BehaviorPattern = TEXT("BehaviorPattern");

AAIController_Boss::AAIController_Boss()
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

void AAIController_Boss::BeginPlay()
{
	Super::BeginPlay();

	RunAI();

}

void AAIController_Boss::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AAIController_Boss::RunAI()
{
	Super::RunAI();

}

void AAIController_Boss::StopAI()
{
	Super::StopAI();
}

//Boss Character에서 호출
void AAIController_Boss::SaveGame(UEGSaveGame * SaveInstance)
{
	if (!SaveInstance)
		return;
	SaveInstance->BossData.ActionTimer = GetBlackboardComponent()->GetValueAsFloat(ActionTimer);
	SaveInstance->BossData.MP = GetBlackboardComponent()->GetValueAsFloat(MP);
	SaveInstance->BossData.bIsDash = GetBlackboardComponent()->GetValueAsBool(IsDash);		
	SaveInstance->BossData.bSoundPlayed = GetBlackboardComponent()->GetValueAsBool(SoundPlayed);
	SaveInstance->BossData.BackStepPoint = GetBlackboardComponent()->GetValueAsVector(BackStepPoint);
	SaveInstance->BossData.BehaviorPattern = GetBlackboardComponent()->GetValueAsEnum(BehaviorPattern);
	EGLOG(Error, TEXT("Boss Save Complete"));
}
//에서 호출
void AAIController_Boss::LoadGame(const UEGSaveGame * LoadInstance)
{
	if (!LoadInstance)
		return;
	GetBlackboardComponent()->SetValueAsFloat(ActionTimer,LoadInstance->BossData.ActionTimer );
	GetBlackboardComponent()->SetValueAsFloat(MP, LoadInstance->BossData.MP);
	GetBlackboardComponent()->SetValueAsBool(IsDash, LoadInstance->BossData.bIsDash);
	GetBlackboardComponent()->SetValueAsBool(SoundPlayed, LoadInstance->BossData.bSoundPlayed);
	GetBlackboardComponent()->SetValueAsVector(BackStepPoint, LoadInstance->BossData.BackStepPoint);
	GetBlackboardComponent()->SetValueAsEnum(BehaviorPattern, LoadInstance->BossData.BehaviorPattern);
	EGLOG(Error, TEXT("Boss Load Complete MP : %f"),GetBlackboardComponent()->GetValueAsFloat(MP));
}
