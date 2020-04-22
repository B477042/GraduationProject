// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialNotify.h"
#include "EGPlayerController.h"
#include "EGPlayerCharacter.h"
//#include "Components/BoxComponent.h"

// Sets default values
ATutorialNotify::ATutorialNotify()
{
	Axis = CreateDefaultSubobject<USceneComponent>(TEXT("Axis"));
	RootComponent = Axis;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	initBoxComponent();
	initTextRenderer();

	NotifyType = ENotifyType::E_None;
	//auto BoxCom = Cast<UBoxComponent>(GetCollisionComponent());
	TextRenderer->SetHiddenInGame(true);
	//BoxCom->SetBoxExtent(FVector(X = 98.860458, Y = 91.200172, Z = 99.117844));
	//SetActorHiddenInGame(false);
}

// Called when the game starts or when spawned
void ATutorialNotify::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger->SetBoxExtent(FVector(194.383270, 200.163177,  152.044571));
	setInfo();
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

	//EGLOG(Warning, TEXT("Welcom player"));
	
	
	TextRenderer->SetHiddenInGame(false);

	FVector Start = GetActorLocation() + TextRenderer->GetRelativeLocation();
	FVector Target = OtherActor->GetActorLocation();

	//Start지점에서 Target지점을 바라볼 때 벡터를 연산한다
	FRotator rotateTo=UKismetMathLibrary::FindLookAtRotation(Start,Target)/*+FRotator(0.0f,180.0f,0.0f)*/;
	//FRotator rotateTo = OtherActor->GetActorRotation();
	TextRenderer->SetWorldRotation(rotateTo);
	//SetActorRotation(rotateTo);
	
}

void ATutorialNotify::OnOverlapEnd(AActor * OvelappedActor, AActor * OtherActor)
{
	if (!checkOverlappedActor((OtherActor)))return;
//	EGLOG(Warning, TEXT("Goodbye player"));

	//TextRenderer->SetText(TEXT("Good Bye Bro"));

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

	TextRenderer->SetText(TEXT("Set Message on editor"));

	TextRenderer->SetTextRenderColor(FColor(0,87,85,255));
	
}

void ATutorialNotify::initBoxComponent()
{
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxTrigger->SetCollisionProfileName(TEXT("Trigger"));
	
	BoxTrigger->SetGenerateOverlapEvents(true);
	float X, Y, Z;
	BoxTrigger->SetBoxExtent(FVector(X = 194.383270, Y = 200.163177, Z = 152.044571));
	BoxTrigger->SetHiddenInGame(true);
	BoxTrigger->SetupAttachment(RootComponent);
}

void ATutorialNotify::setInfo()
{
	switch (NotifyType)
	{
	case ENotifyType::E_MoveInput:
		TextRenderer->SetText(TEXT("Press\nW,A,S,D\nTo Move"));
		break;
	case ENotifyType::E_MouseInput:
		TextRenderer->SetText(TEXT("Move Your Mouse\nAnd Look\nAround"));
		break;
	case ENotifyType::E_Jump:
		TextRenderer->SetText(TEXT("Press Space\nTo Jump"));
		break;
	case ENotifyType::E_AttackInput:
		TextRenderer->SetText(TEXT("Click LMB\nTo Attack"));
		break;
	case ENotifyType::E_GruntEnemy:
		TextRenderer->SetText(TEXT("Watch Out\nThat Robot"));
		break;
	case ENotifyType::E_TrapFire:
		TextRenderer->SetText(TEXT("Be Careful\nFire Ball"));
		break;
	case ENotifyType::E_Trap_Shutter:
		TextRenderer->SetText(TEXT("Spear Could\nBe Destroy"));
		break;
	case ENotifyType::E_Lightning:
		TextRenderer->SetText(TEXT("Don't Touch\nLightning"));
			break;
	case ENotifyType::E_HealBox:
		TextRenderer->SetText(TEXT("Contact Box\nYou'll Recover"));
		break;
	case ENotifyType::E_Claymore:
		TextRenderer->SetText(TEXT("Claymore is\nNot Your\nFriend"));
		break;
	case ENotifyType::E_ChargeAttack:
		TextRenderer->SetText(TEXT("While Attack\nClick RMB\nCharge Attack"));
		break;

	case ENotifyType::E_None:
		//에디터에서 메시지를 적어서 사용해야될 때 사용한다
		//TextRenderer->SetText(TEXT("PLZ SET NOTIFYYYYYYYY"));
		break;
	}
}


//// Called every frame
//void ATutorialNotify::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

