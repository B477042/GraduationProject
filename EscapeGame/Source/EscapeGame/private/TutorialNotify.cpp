// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialNotify.h"
#include "EGPlayerController.h"
#include "EGPlayerCharacter.h"
#include "Engine/Font.h"
//#include "Components/BoxComponent.h"

// Sets default values
ATutorialNotify::ATutorialNotify()
{
	Axis = CreateDefaultSubobject<USceneComponent>(TEXT("Axis"));
	RootComponent = Axis;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	initBoxComponent();
	initTextRenderer();

	NotifyType = ENotifyType::E_None;
	//auto BoxCom = Cast<UBoxComponent>(GetCollisionComponent());
	TextRenderer->SetHiddenInGame(true);
	EnteredPlayer = nullptr;
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

	EnteredPlayer = Other;
	return true;
}

void ATutorialNotify::OnOverlapBegin(AActor * OvelappedActor, AActor * OtherActor)
{
	if (!checkOverlappedActor((OtherActor)))return;

	//EGLOG(Warning, TEXT("Welcom player"));
	
	
	TextRenderer->SetHiddenInGame(false);

	EnteredPlayer = OtherActor;
	rotateTextToPlayer();
	//FVector Start = GetActorLocation() + TextRenderer->GetRelativeLocation();
	//FVector Target = OtherActor->GetActorLocation();

	////Start지점에서 Target지점을 바라볼 때 벡터를 연산한다
	//FRotator rotateTo=UKismetMathLibrary::FindLookAtRotation(Start,Target)/*+FRotator(0.0f,180.0f,0.0f)*/;
	////FRotator rotateTo = OtherActor->GetActorRotation();
	//TextRenderer->SetWorldRotation(rotateTo);
	////SetActorRotation(rotateTo);
	//
	//틱을 켜준다
	
}

void ATutorialNotify::OnOverlapEnd(AActor * OvelappedActor, AActor * OtherActor)
{
	if (!checkOverlappedActor((OtherActor)))return;

	TextRenderer->SetHiddenInGame(true);
	//Tick을 꺼준다
	//PrimaryActorTick.bCanEverTick = false;
	EnteredPlayer = nullptr;
}

void ATutorialNotify::initTextRenderer()
{
	ff
	TextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderer"));
	TextRenderer->SetupAttachment(RootComponent);
	TextRenderer->SetRelativeLocation(FVector(0.0f, 60.0f, 0.0f));
	//TextRenderer->bHiddenInGame = true;
	
	static ConstructorHelpers::FObjectFinder<UFont>FONT(TEXT("Font'/Game/MyFolder/Font/NanumGothic.NanumGothic'"));
	if(FONT.Succeeded())
	TextRenderer->SetFont(FONT.Object);

	TextRenderer->SetHiddenInGame(true);

	TextRenderer->SetText(FText::FromString("Set Message on editor"));
	
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
		TextRenderer->SetText(FText::FromString("Press\nW,A,S,D\nTo Move"));
		break;
	case ENotifyType::E_MouseInput:
		TextRenderer->SetText(FText::FromString("Move Your Mouse\nAnd Look\nAround"));
		break;
	case ENotifyType::E_Jump:
		TextRenderer->SetText(FText::FromString("Press Space\nTo Jump"));
		break;
	case ENotifyType::E_AttackInput:
		TextRenderer->SetText(FText::FromString("Click LMB\nTo Attack"));
		break;
	case ENotifyType::E_GruntEnemy:
		TextRenderer->SetText(FText::FromString("Watch Out\nThat Robot"));
		break;
	case ENotifyType::E_TrapFire:
		TextRenderer->SetText(FText::FromString("Be Careful\nFire Ball"));
		break;
	case ENotifyType::E_Trap_Shutter:
		TextRenderer->SetText(FText::FromString("Spear Could\nBe Destroy"));
		break;
	case ENotifyType::E_Lightning:
		TextRenderer->SetText(FText::FromString("Don't Touch\nLightning"));
			break;
	case ENotifyType::E_HealBox:
		TextRenderer->SetText(FText::FromString("Contact Box\nYou'll Recover"));
		break;
	case ENotifyType::E_Claymore:
		TextRenderer->SetText(FText::FromString("Claymore is\nNot Your\nFriend"));
		break;
	case ENotifyType::E_ChargeAttack:
		TextRenderer->SetText(FText::FromString("While Attack\nClick RMB\nCharge Attack"));
		break;

	case ENotifyType::E_None:
		//에디터에서 메시지를 적어서 사용해야될 때 사용한다
		//TextRenderer->SetText(TEXT("PLZ SET NOTIFYYYYYYYY"));
		break;
	}
}

void ATutorialNotify::rotateTextToPlayer()
{
	if (EnteredPlayer == nullptr)
	{
		EGLOG(Warning, TEXT("Entered is nullptr"));
		return;
	}
	EGLOG(Warning, TEXT("Entered is not nullptr"));
	FVector Start = GetActorLocation() + TextRenderer->GetRelativeLocation();
	FVector Target = EnteredPlayer ->GetActorLocation();

	//Start지점에서 Target지점을 바라볼 때 벡터를 연산한다
	FRotator rotateTo = UKismetMathLibrary::FindLookAtRotation(Start, Target)/*+FRotator(0.0f,180.0f,0.0f)*/;
	//FRotator rotateTo = OtherActor->GetActorRotation();
	TextRenderer->SetWorldRotation(rotateTo);
	//SetActorRotation(rotateTo);
}


//// Called every frame
void ATutorialNotify::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

