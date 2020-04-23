// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn_Camera.h"
#include "NPCCharacter.h"
#include "DialogueWidget.h"
#include "Tutorial_Controller.h"

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

	float X, Y, Z, Roll, Yaw, Pitch;
	SetActorLocationAndRotation(FVector(X = -10.000000, Y = 230.000000, Z = 40.000000), FRotator(Pitch = 0.000000, Yaw = -90.000114, Roll = 0.000000));
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
	EGLOG(Warning,*Diagram.ToString() );
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
	//player의 컨트롤러를 casting한다
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
	//Widget에 이름을 적어준다
	widget->SetTalker(tempTalker, FText::FromString(tempTalker->GetName()));
	
	EGLOG(Error, TEXT("I Told U!!!!!"));
}

void APawn_Camera::OnNextClicked()
{
}

void APawn_Camera::OnPrevClicked()
{
}

