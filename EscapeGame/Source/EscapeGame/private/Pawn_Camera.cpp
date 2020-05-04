// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_Camera.h"
#include "NPCCharacter.h"
#include "DialogueWidget.h"
#include "Tutorial_Controller.h"

int APawn_Camera::n_Act = 0;

// Sets default values
APawn_Camera::APawn_Camera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	BoxCollision= CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxCollision;
	//BoxCollision->SetupAttachment(RootComponent);
	Cam->SetupAttachment(RootComponent);
	BoxCollision->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	BoxCollision -> SetCollisionProfileName(TEXT("PlayerCharacter"));
	//BoxCollision->SetGenerateOverlapEvents(true);

	
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_DIALOGUE(TEXT("DataTable'/Game/MyFolder/DataTable/Dialogue.Dialogue'"));
	if (DT_DIALOGUE.Succeeded())
	{
		dialogueTable = DT_DIALOGUE.Object;
	}
}

// Called when the game starts or when spawned
void APawn_Camera::BeginPlay()
{
	Super::BeginPlay();
	float X, Y, Z, Roll, Yaw, Pitch;
	SetActorLocationAndRotation(FVector(X = -10.000000, Y = 230.000000, Z = 40.000000), FRotator(Pitch = 0.000000, Yaw = -90.000114, Roll = 0.000000));
	/*auto tempCon = Cast<ATutorial_Controller>(GetController());
	if (tempCon != nullptr)
		MyController = tempCon;*/
}



// Called every frame
void APawn_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APawn_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawn_Camera::ListenTalk(TWeakObjectPtr<ACharacter> Talker, FText Diagram)
{
	auto tempController = Cast<ATutorial_Controller>(Controller);
	if (tempController == nullptr)
	{
		EGLOG(Warning, TEXT("Temp Controller failed"));
		return;
	}


	auto widget = Cast<UDialogueWidget>(tempController->UIWidgetInstance);
	if (widget == nullptr)
	{
		EGLOG(Warning, TEXT("Temp widget failed"));
		return;
	}
	//EGLOG(Warning,*FString::Printf(Diagram) );
	widget->RecieveDiagram(Diagram);

}

void APawn_Camera::StartListenTo(TWeakObjectPtr<ACharacter>Talker)
{
	auto tempTalker = Cast<ANPCCharacter>(Talker);
	//Casting Test
	if (tempTalker==nullptr)
	{
		EGLOG(Warning, TEXT("Temp Talker failed"));
		return;
	}
	//player�� ��Ʈ�ѷ��� casting�Ѵ�
	auto tempController = Cast<ATutorial_Controller>(Controller);
	if (tempController==nullptr)
	{ 
		EGLOG(Warning, TEXT("Temp Controller failed"));
		return;
	}

	
	auto widget = Cast<UDialogueWidget>(tempController->UIWidgetInstance);
	if (widget == nullptr)
	{
		EGLOG(Warning, TEXT("Temp widget failed"));
		return;
	}
	//Widget�� �̸��� �����ش�
	widget->SetTalker(tempTalker, FText::FromString(tempTalker->GetName()));
	
	EGLOG(Error, TEXT("I Told U!!!!!"));
}
 
void APawn_Camera::OnNextClicked()
{
}

void APawn_Camera::OnPrevClicked()
{
}

void APawn_Camera::findTalkers()
{
	auto Center = GetActorLocation();

	auto World = GetWorld();
	if (World == nullptr)return;
	// Scan 8m
	float DetectRadius = 800.0f;




	//Ž���� ���������� �����
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);


	//��� ���͸� Overlap �������� ã�Ƴ���. ����� DetectRadius���� ��
	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);



	if (bResult)
	{
		//Ž���� ���͵鿡�� npc character�� ã�� a_Talker�� �־��ݴϴ�
		for (auto OverlapResult : OverlapResults)
		{
			auto tempActor = Cast<ANPCCharacter>(OverlapResult.Actor);
			if(tempActor==nullptr)continue;
			a_Talkers.Add(tempActor);

		}
	}


}

void APawn_Camera::loadDialogue()
{

}


