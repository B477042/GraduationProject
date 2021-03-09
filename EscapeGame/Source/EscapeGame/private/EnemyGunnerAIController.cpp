// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGunnerAIController.h"

#include "EGPlayerCharacter.h"
#include "EGPlayerController.h"


AEnemyGunnerAIController::AEnemyGunnerAIController()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB_Data(TEXT("BlackboardData'/Game/MyFolder/AIData/BB_GunnerBoard.BB_GunnerBoard'"));
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
	
//	FAISenseID
	//AIPerceptionComponent->ConfigureSense

	//https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAISenseConfig_Sight/index.html
	//UAISenseConfig_Sight Document
	//AISenseConfig_Sight senseConfig_Sight;
	AiConfigSight->SightRadius = 1500.0f;
	AiConfigSight->LoseSightRadius = 1600.0f;
	AiConfigSight->PeripheralVisionAngleDegrees = 60.0f;
	AiConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AiConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	AiConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
	AiConfigSight->SetMaxAge(1.0f);


	PerceptionComponent->ConfigureSense(*AiConfigSight);
	PerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());


}
void AEnemyGunnerAIController::BeginPlay()
{
	Super::BeginPlay();
	//RunAI();
	//EGLOG(Error,TEXT("ConBegin"))
}

void AEnemyGunnerAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();



	//PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyGunnerAIController::OnPerceptionUpdated);
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyGunnerAIController::OnTargetPerceptionUpdated);
	//PerceptionComponent->GetSenseConfig()
}




void AEnemyGunnerAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void AEnemyGunnerAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyGunnerAIController::RunAI()
{
	Super::RunAI();
	EGLOG(Error, TEXT("Ai Start"));
}

void AEnemyGunnerAIController::StopAI()
{
	Super::StopAI();
}

void AEnemyGunnerAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	//EGLOG(Error, TEXT("something Detected"));
	for (auto it : UpdatedActors)
	{
		EGLOG(Warning, TEXT("hi friend"));
		//범용성을 생각하면 Player controller로 검사하는게 맞는 코드 같다
		AEGPlayerCharacter* tempActor = Cast<AEGPlayerCharacter>(it);
		
		//가장먼저 확인된 player를 타겟으로
		if (tempActor!=nullptr)
		{
			GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, tempActor);
			//EGLOG( Error, TEXT("Target Set"));
			return;
		}

	}

	//검색된 player가 없다면 null로 바꿔준다

	GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
	
	EGLOG(Warning, TEXT("Perception Update! 4446"));

}
void AEnemyGunnerAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	
	//Check Sensed Actor is Controlled by Player
	auto target = Cast<APawn>(Actor);
	if (target == nullptr)return;

	auto targetController = Cast<AEGPlayerController>(target->GetController());
	if (targetController == nullptr)return;



	//Sensed Result.
	//True = Percept Actor Successfully  | False = Loose Actor
	bool bSenseResult = Stimulus.WasSuccessfullySensed();

	if (bSenseResult)
	{
		EGLOG(Error, TEXT("Find %s "), *Actor->GetName());
		GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, Actor);
		return;
	}


	EGLOG(Error, TEXT("Lose %s"), *Actor->GetName());
	GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetPlayer, nullptr);
	GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::TargetPos, Actor->GetActorLocation());
	
		


}
