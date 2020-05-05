// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_Camera.h"

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
	
	
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_DIALOGUE00(TEXT("DataTable'/Game/MyFolder/DataTable/Dialogue_Tutorial.Dialogue_Tutorial'"));
	if (DT_DIALOGUE00.Succeeded())
	{
		dialogueTable.Add( DT_DIALOGUE00.Object);
	}
}

// Called when the game starts or when spawned
void APawn_Camera::BeginPlay()
{
	Super::BeginPlay();
	float X, Y, Z, Roll, Yaw, Pitch;
	SetActorLocationAndRotation(FVector(X = -10.000000, Y = 230.000000, Z = 40.000000), FRotator(Pitch = 0.000000, Yaw = -90.000114, Roll = 0.000000));
	//findTalkers();
	loadDialogue();
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

void APawn_Camera::AddTalkingActor(TWeakObjectPtr<ANPCCharacter> Talker)
{
	
	//EGLOG(Warning,*FString::Printf(Diagram) );
	//widget->PrintLog(Diagram);
	
	auto tempActor = Cast<ANPCCharacter>(Talker);
	if(tempActor!=nullptr)
		a_Talkers.Add(Talker);
	EGLOG(Warning, TEXT("%s joined to talking"), *Talker->GetName());
}

void APawn_Camera::StartListenTo(TWeakObjectPtr<ANPCCharacter>Talker)
{
	//auto tempTalker = Cast<ANPCCharacter>(Talker);
	////Casting Test
	//if (tempTalker==nullptr)
	//{
	//	EGLOG(Warning, TEXT("Temp Talker failed"));
	//	return;
	//}
	

	
	auto widget = getWidget();
	if (!widget)return;
	//Widget에 이름을 적어준다
	//widget->SetTalker(Talker, FText::FromString(Talker->GetName()));
	
	EGLOG(Error, TEXT("I Told U!!!!!"));
}
 
void APawn_Camera::OnNextClicked()
{
}

void APawn_Camera::OnPrevClicked()
{
}



void APawn_Camera::loadDialogue()
{
	
	for (int i = 0; i < 100; i++)
	{
		auto tempData = dialogueTable[n_Act]->FindRow<FDialogueTableRow>(FName(*FString::FormatAsNumber(i)), FString(""));
		if (tempData == nullptr) { 
			EGLOG(Warning, TEXT("Load Dialouge failed at : %d"), i);
			break; }
		
		dialogues.Add(*tempData);

		EGLOG(Warning, TEXT("Load Dialouge times: %d"),i);
		
		
	}
	

	n_Act++;
}

void APawn_Camera::startTalk()
{

}

void APawn_Camera::nextLog()
{
}

void APawn_Camera::prevLog()
{
}

UDialogueWidget * APawn_Camera::getWidget()
{
	auto tempController = Cast<ATutorial_Controller>(Controller);
	if (tempController == nullptr)
	{
		EGLOG(Warning, TEXT("Temp Controller failed"));
		return nullptr;
	}


	auto widget = Cast<UDialogueWidget>(tempController->UIWidgetInstance);
	if (widget == nullptr)
	{
		EGLOG(Warning, TEXT("Temp widget failed"));
		return nullptr;
	}
	return widget;
}


