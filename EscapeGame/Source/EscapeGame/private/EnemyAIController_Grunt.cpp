// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController_Grunt.h"
#include "DT_DataStruct.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "EGPlayerCharacter.h"
#include "EGPlayerController.h"


AEnemyAIController_Grunt::AEnemyAIController_Grunt()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_GruntBoard.BB_GruntBoard'"));
	if (BB.Succeeded())
	{
		BBData = BB.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("BehaviorTree'/Game/MyFolder/AIData/BT_GruntEnemyTree.BT_GruntEnemyTree'"));
	if (BT.Succeeded())
	{
		BTData = BT.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_GRUNT(TEXT("DataTable'/Game/MyFolder/DataTable/DT_GruntType.DT_GruntType'"));
	if (DT_GRUNT.Succeeded())
	{
		DT_Grunt = DT_GRUNT.Object;
	}
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PERCEPTIONCOMPONENT"));
	AiConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AIConfigSight"));

	AiConfigSight->SightRadius = 1500.0f;
	AiConfigSight->LoseSightRadius = 1600.0f;
	AiConfigSight->PeripheralVisionAngleDegrees = 60.0f;
	AiConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AiConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	AiConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
	AiConfigSight->SetMaxAge(10.0f);


	PerceptionComponent->ConfigureSense(*AiConfigSight);
	PerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());

	
}

const UDataTable * AEnemyAIController_Grunt::GetDT_Grunt()
{
	return DT_Grunt;
}

void AEnemyAIController_Grunt::BeginPlay()
{
	Super::BeginPlay();
	RunAI();
}

void AEnemyAIController_Grunt::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController_Grunt::OnTargetPerceptionUpdated);
}

void AEnemyAIController_Grunt::RunAI()
{
	Super::RunAI();
	
	
}

void AEnemyAIController_Grunt::StopAI()
{
	Super::StopAI();
}

void AEnemyAIController_Grunt::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (auto it : UpdatedActors)
	{
		EGLOG(Warning, TEXT("hi friend"));
		//범용성을 생각하면 Player controller로 검사하는게 맞는 코드 같다
		AEGPlayerCharacter* tempActor = Cast<AEGPlayerCharacter>(it);

		//가장먼저 확인된 player를 타겟으로
		if (tempActor != nullptr)
		{
			GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, tempActor);
			//EGLOG( Error, TEXT("Target Set"));
			return;
		}

	}

	//검색된 player가 없다면 null로 바꿔준다

	GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);

}

void AEnemyAIController_Grunt::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
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
		EGLOG(Error, TEXT("Find %s "), *Actor->GetName());
		GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, Actor);
		return;
	}

	//실패시 관련 BB값 초기화
	EGLOG(Error, TEXT("Lose %s"), *Actor->GetName());
	GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
	GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::TargetPos, Actor->GetActorLocation());

}
