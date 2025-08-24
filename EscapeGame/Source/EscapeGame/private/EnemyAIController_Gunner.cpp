// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Controller/EnemyAIController_Gunner.h"

#include "Actor/Character/EGPlayerController.h"
#include "GameFramework/Character.h"
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
	
	AiConfigHearing->HearingRange = 550;
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
		//���뼺�� �����ϸ� Player controller�� �˻��ϴ°� �´� �ڵ� ����
		AEGPlayerController* TempCon = Cast<AEGPlayerController>(TempCharacter->GetController());

		//������� Ȯ�ε� player�� Ÿ������
		if (TempCon!=nullptr)
		{

			GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, TempCharacter);
			EGLOG( Error, TEXT("Target Set"));
			return;
		}

	}

	//�˻��� player�� ���ٸ� null�� �ٲ��ش�
	EGLOG(Log, TEXT("Lost Target"));
	GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
	
	//EGLOG(Warning, TEXT("Perception Update! 4446"));

}
void AEnemyAIController_Gunner::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//EGLOG(Log, TEXT("Hi : %s"), *Actor->GetName());
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
		EGLOG(Log, TEXT("Find %s "), *Actor->GetName());
		GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, Actor);
		return;
	}

	//���н� ���� BB�� �ʱ�ȭ
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
