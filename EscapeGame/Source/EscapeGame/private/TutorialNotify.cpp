// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialNotify.h"
#include "EGPlayerController.h"
#include "EGPlayerCharacter.h"
//#include "Components/BoxComponent.h"

// Sets default values
ATutorialNotify::ATutorialNotify()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	
	initTextRenderer();

	NotifyType = ENotifyType::E_None;
	auto BoxCom = Cast<UBoxComponent>(GetCollisionComponent());
	float X, Y, Z;
	BoxCom->SetBoxExtent(FVector(X = 98.860458, Y = 91.200172, Z = 99.117844));

}

// Called when the game starts or when spawned
void ATutorialNotify::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ATutorialNotify::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddDynamic(this, &ATutorialNotify::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATutorialNotify::OnOverlapEnd);
	
}

bool ATutorialNotify::checkOverlappedActor(AActor * Other)
{
	auto otherChara = Cast<AEGPlayerCharacter>(Other);
	if (otherChara == nullptr)return false;


	return true;
}

void ATutorialNotify::OnOverlapBegin(AActor * OvelappedActor, AActor * OtherActor)
{
	if (!checkOverlappedActor((OtherActor)))return;

	EGLOG(Warning, TEXT("Welcom player"));
	TextRenderer->SetText(TEXT("Welcome Bro"));
	
	TextRenderer->SetHiddenInGame(false);
	if (TextRenderer->bHiddenInGame != false)
		EGLOG(Error, TEXT("bHidden in game isnot flase"));

}

void ATutorialNotify::OnOverlapEnd(AActor * OvelappedActor, AActor * OtherActor)
{
	if (!checkOverlappedActor((OtherActor)))return;
	EGLOG(Warning, TEXT("Goodbye player"));

	TextRenderer->SetText(TEXT("Good Bye Bro"));

	//TextRenderer->bHiddenInGame = true;
	TextRenderer->SetHiddenInGame(true);
}

void ATutorialNotify::initTextRenderer()
{

	TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
	TextRenderer->SetupAttachment(RootComponent);
	TextRenderer->SetRelativeLocation(FVector(0.0f, 60.0f, 0.0f));
	//TextRenderer->bHiddenInGame = true;
	TextRenderer->SetHiddenInGame(true);



	TextRenderer->SetText(TEXT("Welcome Bro"));

	TextRenderer->SetTextRenderColor(FColor(0,87,85,255));
	
}

//void ATutorialNotify::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	if (!checkOverlappedActor((OtherActor)))return;
//	
//	EGLOG(Warning, TEXT("Welcom player"));
//}
//
//void ATutorialNotify::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
//{
//	if (!checkOverlappedActor((OtherActor)))return;
//	EGLOG(Warning, TEXT("Goodbye player"));
//}

//// Called every frame
//void ATutorialNotify::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

