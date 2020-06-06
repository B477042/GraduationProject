// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_Camera.h"
#include "NPCCharacter.h"
#include "DialogueWidget.h"
#include "Tutorial_Controller.h"

//int APawn_Camera::n_Act = 0;

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
	
	c_Talk = 0;
	maxLine = 0;
	bIsDelegateRegist = false;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_DIALOGUE00(TEXT("DataTable'/Game/MyFolder/DataTable/Dialogue_Tutorial.Dialogue_Tutorial'"));
	if (DT_DIALOGUE00.Succeeded())
	{
		dialogueTable =DT_DIALOGUE00.Object;
	}
	//static ConstructorHelpers::FObjectFinder<UDataTable>DT_DIALOGUE00(TEXT("DataTable'/Game/MyFolder/DataTable/Dialogue_Tutorial.Dialogue_Tutorial'"));
	//if (DT_DIALOGUE00.Succeeded())
	//{
	//	dialogueTable.Add( DT_DIALOGUE00.Object);
	//}
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
	
	if (!bIsDelegateRegist)registDelegateToWidget();
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
	//하나라도 참가 했으니 한번 출력한다
	startTalk();
}
 
void APawn_Camera::OnNextClicked()
{
	nextLog();
}

void APawn_Camera::OnPrevClicked()
{
	prevLog();
}



void APawn_Camera::loadDialogue()
{
	
	for (int i = 0; i < 100; i++)
	{
		auto tempData = dialogueTable->FindRow<FDialogueTableRow>(FName(*FString::FormatAsNumber(i)), FString(""));
		if (tempData == nullptr) { 
			EGLOG(Warning, TEXT("Load Dialouge failed at : %d"), i);
			break; }
		
		dialogues.Add(*tempData);
		maxLine++;
		EGLOG(Warning, TEXT("Load Dialouge times: %d"),i);
		
		
	}
	

	//n_Act++;
}

void APawn_Camera::startTalk()
{
	getWidget()->NextStage = TEXT("Stage1");
	printLog();
	c_Talk++;
	
}

void APawn_Camera::nextLog()
{
	if (c_Talk > maxLine)
	{

	}
	printLog();
	c_Talk++;
	
}


void APawn_Camera::prevLog()
{
	
	printLog();
	if(c_Talk>=1)
		c_Talk--;
	
}

void APawn_Camera::printLog()
{
	//대화를 다 읽었을경우
	if (c_Talk >= maxLine)
	{
		//n_Act++;
		UGameplayStatics::OpenLevel(this, "Stage1");
		return;
	}
	FDialogueTableRow* tempDialogue = &dialogues[c_Talk];
	auto widget = getWidget();
	if (tempDialogue==nullptr || widget == nullptr)return;

	widget->SetTalkerName(tempDialogue->Talker);
	widget->PrintLog(FText::FromString(tempDialogue->Dialogue));
	
}

void APawn_Camera::registDelegateToWidget()
{


	auto tempWidget = getWidget();
	if (!tempWidget)
	{
		EGLOG(Error, TEXT("Can't Access Widget"));
		return;
	}

	tempWidget->OnClickNextDelegate.AddDynamic(this, &APawn_Camera::OnNextClicked);
	tempWidget->OnClickPrevDelegate.AddDynamic(this, &APawn_Camera::OnPrevClicked);
	bIsDelegateRegist = true;


	
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


