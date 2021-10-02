// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController_Gunner.h"

#include "EGPlayerCharacter.h"
#include "EGPlayerController.h"
FName AEnemyAIController_Gunner::SoundPlayed = TEXT("SoundPlayed");

AEnemyAIController_Gunner::AEnemyAIController_Gunner()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB_Data(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_GunnerBoad.BB_GunnerBoad'"));
	if (BB_Data.Succeeded())
	{
		BBData = BB_Data.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT_DATA(TEXT("BehaviorTree'/Game/MyFolder/AIData/BT_GunnerTree.BT_GunnerTree'"));
	if (BT_DATA.Succeeded())
	{
		BTData = BT_DATA.Object;
	}

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PERCEPTIONCOMPONENT"));
	AiConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIConfigSight"));
	AiConfigHearing = CreateDefaultSubobject < UAISenseConfig_Hearing>(TEXT("AIConfigHearing"));
//	FAISenseID
	//AIPerceptionComponent->ConfigureSense
	AiConfigSight->SightRadius = 1500.0f;
	AiConfigSight->LoseSightRadius = 1600.0f;
	AiConfigSight->PeripheralVisionAngleDegrees = 60.0f;
	AiConfigSight->AutoSuccessRangeFromLastSeenLocation = 500.0f;
	AiConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AiConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	AiConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
	AiConfigSight->SetMaxAge(10.0f);
	//Hearing Setting
	AiConfigHearing->HearingRange = 500;
	AiConfigHearing->LoSHearingRange = 550;
	AiConfigHearing->DetectionByAffiliation.bDetectFriendlies = true;
	AiConfigHearing->DetectionByAffiliation.bDetectEnemies = true;
	AiConfigHearing->DetectionByAffiliation.bDetectNeutrals = true;
	AiConfigHearing->SetMaxAge(5.0f);
	
	//Regist Ai Sense
	PerceptionComponent->ConfigureSense(*AiConfigSight);
	PerceptionComponent->ConfigureSense(*AiConfigHearing);
	//PerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
	//PerceptionComponent->SetSenseEnabled(UAISense_Hearing::StaticClass(), true);
	


}
void AEnemyAIController_Gunner::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AEnemyAIController_Gunner::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	//SetUpAiPerception();
	//PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController_Gunner::OnPerceptionUpdated);
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController_Gunner::OnTargetPerceptionUpdated);
	//PerceptionComponent->OnPerceptionUpdated
	//PerceptionComponent->GetSenseConfig()
}




void AEnemyAIController_Gunner::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void AEnemyAIController_Gunner::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyAIController_Gunner::RunAI()
{
	Super::RunAI();
	EGLOG(Error, TEXT("Ai Start"));
}

void AEnemyAIController_Gunner::StopAI()
{
	Super::StopAI();
}

void AEnemyAIController_Gunner::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	 
	for (auto it : UpdatedActors)
	{
		 
		
		ACharacter* TempCharacter = Cast<ACharacter>(it);
		if (!TempCharacter)
		{
			continue;
		}
		//범용성을 생각하면 Player controller로 검사하는게 맞는 코드 같다
		AEGPlayerController* TempCon = Cast<AEGPlayerController>(TempCharacter->GetController());

		//가장먼저 확인된 player를 타겟으로
		if (TempCon!=nullptr)
		{

			GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, TempCharacter);
			EGLOG( Error, TEXT("Target Set"));
			return;
		}

	}

	//검색된 player가 없다면 null로 바꿔준다
	EGLOG(Log, TEXT("Lost Target"));
	GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
	
	//EGLOG(Warning, TEXT("Perception Update! 4446"));

}
void AEnemyAIController_Gunner::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//EGLOG(Log, TEXT("Hi : %s"), *Actor->GetName());
	//감지된 엑터가 player인지 검사합니다
	auto target = Cast<APawn>(Actor);
	if (target == nullptr)return;

	auto targetController = Cast<AEGPlayerController>(target->GetController());
	if (targetController == nullptr)return;



	//탐지결과
	//True = 감지 성공  | False = 사라짐
	bool bSenseResult = Stimulus.WasSuccessfullySensed();
	
	//성공시 값을 저장하고 return
	if (bSenseResult)
	{
		EGLOG(Log, TEXT("Find %s "), *Actor->GetName());
		GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, Actor);
		return;
	}

	//실패시 관련 BB값 초기화
	EGLOG(Log, TEXT("Lose %s"), *Actor->GetName());
	GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
	GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::TargetPos, Actor->GetActorLocation());
	GetBlackboardComponent()->SetValueAsBool(AEnemyAIController_Gunner::SoundPlayed, false);
		


}

//void AEnemyAIController_Gunner::SetUpAiPerception()
//{
//
//	//https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAISenseConfig_Sight/index.html
//	//UAISenseConfig_Sight Document
//	//AISenseConfig_Sight senseConfig_Sight;
//	AiConfigSight->SightRadius = SightRadius;
//	AiConfigSight->LoseSightRadius = LoseSightRadius;
//	AiConfigSight->AutoSuccessRangeFromLastSeenLocation = 1500.0f;
//	AiConfigSight->PeripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;
//	AiConfigSight->DetectionByAffiliation.bDetectEnemies = true;
//	AiConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
//	AiConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
//	AiConfigSight->SetMaxAge(MaxAge);
//
//	//Hearing Setting
//	AiConfigHearing->HearingRange = HearingRange;
//	AiConfigHearing->LoSHearingRange = LoSHearingRange;
//	AiConfigHearing->DetectionByAffiliation.bDetectFriendlies = true;
//	AiConfigHearing->DetectionByAffiliation.bDetectEnemies = true;
//	AiConfigHearing->DetectionByAffiliation.bDetectNeutrals = true;
//	AiConfigHearing->SetMaxAge(MaxAge);
//
//
//}
