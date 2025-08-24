// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Controller/EnemyAIController_Grunt.h"

#include "Actor/Character/EGPlayerCharacter.h"
#include "Actor/Character/EGPlayerController.h"
#include "Perception/AIPerceptionComponent.h"

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
	AiConfigSight->AutoSuccessRangeFromLastSeenLocation = 1500.0f;
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
		//���뼺�� �����ϸ� Player controller�� �˻��ϴ°� �´� �ڵ� ����
		AEGPlayerCharacter* tempActor = Cast<AEGPlayerCharacter>(it);

		//������� Ȯ�ε� player�� Ÿ������
		if (tempActor != nullptr)
		{
			GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, tempActor);
			//EGLOG( Error, TEXT("Target Set"));
			return;
		}

	}

	//�˻��� player�� ���ٸ� null�� �ٲ��ش�

	GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);

}

void AEnemyAIController_Grunt::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//������ ���Ͱ� player���� �˻��մϴ�
	auto target = Cast<APawn>(Actor);
	if (target == nullptr)return;

	auto targetController = Cast<AEGPlayerController>(target->GetController());
	if (targetController == nullptr)return;



	//Ž�����
	//True = ���� ����  | False = �����
	bool bSenseResult = Stimulus.WasSuccessfullySensed();

	//������ ���� �����ϰ� return
	if (bSenseResult)
	{
		EGLOG(Error, TEXT("Find %s "), *Actor->GetName());
		GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, Actor);
		return;
	}

	//���н� ���� BB�� �ʱ�ȭ
	EGLOG(Error, TEXT("Lose %s"), *Actor->GetName());
	GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
	GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::TargetPos, Actor->GetActorLocation());

}
