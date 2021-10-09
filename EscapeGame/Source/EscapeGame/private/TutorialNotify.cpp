// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialNotify.h"
#include "EGPlayerController.h"
#include "EGPlayerCharacter.h"
#include "Engine/Font.h"
#include "EGSaveGame.h"
#include "EGGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "DT_DataStruct.h"
//#include "Components/BoxComponent.h"



// Sets default values
ATutorialNotify::ATutorialNotify()
{
	Axis = CreateDefaultSubobject<USceneComponent>(TEXT("Axis"));
	RootComponent = Axis;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	initBoxComponent();
	
	//static ConstructorHelpers::FClassFinder<UUserWidget>UI_TUTO_C(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_Tutorial.UI_Tutorial_C'"));
	//if (UI_TUTO_C.Succeeded())
	//{
	//	TutoWidgetClass = UI_TUTO_C.Class;
	//
	//}

	static ConstructorHelpers::FObjectFinder<UDataTable>DT_TUTORIAL(TEXT("DataTable'/Game/MyFolder/DataTable/DT_TutorialNotifyMessages.DT_TutorialNotifyMessages'"));
	if (DT_TUTORIAL.Succeeded())
	{
		DT_Tutorial = DT_TUTORIAL.Object;
	}

	
	bIsImportant = false;
	bIsNotifyed = false;
	NotifyType = ENotifyType::E_None;



	/*const TMap<ENotifyType, FName>ATutorialNotify::*/SetOfTypesOfNotifications = {
	{ENotifyType::E_None,TEXT("None")},
	{ENotifyType::E_AttackInput,TEXT("AttackInput")},
	{ENotifyType::E_ChargeAttack,TEXT("ChargeAttack")},
	{ENotifyType::E_Claymore,TEXT("Claymore")},
	{ENotifyType::E_FireBallTrap,TEXT("FireBallTrap")},
	{ENotifyType::E_HealBox,TEXT("HealBox")},
	{ENotifyType::E_GameRule,TEXT("GameRule")},
	{ENotifyType::E_Jump,TEXT("Jump")},
	{ENotifyType::E_Lightning,TEXT("Lightning")},
	{ENotifyType::E_MoveInput,TEXT("MoveInput")},
	{ENotifyType::E_GoldenGate ,TEXT("GoldenGate")},
	{ENotifyType::E_SubBattery,TEXT("SubBattery")},
	{ENotifyType::E_GruntEnemy,TEXT("Grunt")},
	{ENotifyType::E_Gunner,TEXT("Gunner")},
	{ENotifyType::E_Boss,TEXT("Boss")},
	{ENotifyType::E_Guard,TEXT("Guard")},
	{ENotifyType::E_ShutterTrap,TEXT("E_ShutterTrap")}
	};


	BoxTrigger->SetBoxExtent(FVector(140.924042, 160.456924, 129.459534));

}

// Called when the game starts or when spawned
void ATutorialNotify::BeginPlay()
{
	Super::BeginPlay();
	
	//TutoWidget = CreateWidget<UTutorialWidget>(GetWorld()->GetFirstPlayerController(), TutoWidgetClass);

	//Widget에 넣을 정보를 불러온다
	

	//auto Controller = Cast<AEGPlayerController>(GetWorld()->GetFirstPlayerController());
	//if (!Controller)return;
	////튜토리얼 메시지를 player controller로 보내서 widget을 준비 시킨다
	//if (!TutoWidget)
	//	TutoWidget = CreateWidget<UTutorialWidget>(Controller, TutoWidgetClass);
	//if (!TutoWidget)
	//	return;
	

}

void ATutorialNotify::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddDynamic(this, &ATutorialNotify::OnOverlapBegin);
	//OnActorEndOverlap.AddDynamic(this, &ATutorialNotify::OnOverlapEnd);
	
	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Gameinstance is not EGGameInstance"));
		return;
	}
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &ATutorialNotify::SaveGame);
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &ATutorialNotify::LoadGame);


}



void ATutorialNotify::OnOverlapBegin(AActor * OvelappedActor, AActor * OtherActor)
{
	if (bIsNotifyed)
	{
		EGLOG(Log, TEXT("%s is Notifyted"), *GetName());
		return;
	}

	auto Player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!Player)return;

	auto Controller = Cast<AEGPlayerController>(Player->GetController());
	if (!Controller)return;
	////튜토리얼 메시지를 player controller로 보내서 widget을 준비 시킨다
	//if (!TutoWidget)
	//	TutoWidget = CreateWidget<UUserWidget>(Controller, TutoWidgetClass);
	//if (!TutoWidget)
	//	return;



	//if (!DT_Tutorial)return;

	//int8 num = (uint8)NotifyType;
	//auto data = DT_Tutorial->FindRow<FTutorialDataTable>(*(FString::FromInt(num)), TEXT(""));
	//if (!data)
	//{
	//	EGLOG(Error, TEXT("Can't Find Tutorial Message on table"));
	//	return;
	//}

	Controller->ShowTutorialMessage((uint8)NotifyType);
	bIsNotifyed = true;

	//TutoWidget->AddToViewport(2);
	
}

void ATutorialNotify::OnOverlapEnd(AActor * OvelappedActor, AActor * OtherActor)
{
	auto Player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!Player)return;
	auto Controller = Cast<AEGPlayerController>(Player->GetController());
	if (!Controller)return;

	Controller->CloseTutorialMessage();
	
 
}



void ATutorialNotify::SaveGame(UEGSaveGame * SaveInstance)
{
	if (!SaveInstance)
	{
		EGLOG(Error, TEXT("SaveInstance is nullptr"));
		return;
	}


}

void ATutorialNotify::LoadGame(const UEGSaveGame * LoadInstance)
{
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("LoadInstance is nullptr"));
		return;
	}


}
void ATutorialNotify::initBoxComponent()
{
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxTrigger->SetCollisionProfileName(TEXT("Trigger"));
	BoxTrigger->SetRelativeLocation(FVector(0, 0, 150));
	BoxTrigger->SetGenerateOverlapEvents(true);
	float X, Y, Z;
	BoxTrigger->SetBoxExtent(FVector(X = 200, Y = 200, Z = 150));
	BoxTrigger->SetHiddenInGame(true);
	BoxTrigger->SetupAttachment(RootComponent);
}
//
//void ATutorialNotify::LoadTutorialData(FTutorialDataTable &Input)
//{
//	if (!TutoWidget)return ;
//
//	auto data = DT_Tutorial->FindRow<FTutorialDataTable>(*ATutorialNotify::SetOfTypesOfNotifications.Find(NotifyType), TEXT(""));
//	if (!data)
//	{
//		EGLOG(Error, TEXT("Can't Find Tutorial Message on table"));
//		return;
//	}
//
//	
//	Input = *data;
//}







