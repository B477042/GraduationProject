// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialNotify.h"
#include "EGPlayerController.h"
#include "EGPlayerCharacter.h"
#include "Engine/Font.h"
#include "EGSaveGame.h"
#include "EGGameInstance.h"
//#include "Components/BoxComponent.h"

const TMap<ENotifyType, FName>ATutorialNotify::SetOfTypesOfNotifications = {
	{ENotifyType::E_None,TEXT("None")},
	{ENotifyType::E_AttackInput,TEXT("AttackInput")},
	{ENotifyType::E_ChargeAttack,TEXT("ChargeAttack")},
	{ENotifyType::E_Claymore,TEXT("Claymore")},
	{ENotifyType::E_FireBallTrap,TEXT("FireBallTrap")},
	{ENotifyType::E_GruntEnemy,TEXT("GruntEnemy")},
	{ENotifyType::E_HealBox,TEXT("HealBox")},
	{ENotifyType::E_HUD,TEXT("HUD")},
	{ENotifyType::E_Jump,TEXT("Jump")},
	{ENotifyType::E_Lightning,TEXT("Lightning")},
	{ENotifyType::E_MouseInput,TEXT("MouseInput")},
	{ENotifyType::E_MoveInput,TEXT("MoveInput")},
	{ENotifyType::E_ShutterTrap,TEXT("E_ShutterTrap")}

};

// Sets default values
ATutorialNotify::ATutorialNotify()
{
	Axis = CreateDefaultSubobject<USceneComponent>(TEXT("Axis"));
	RootComponent = Axis;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	initBoxComponent();
	
	
	
	bIsImportant = false;

	NotifyType = ENotifyType::E_None;
}

// Called when the game starts or when spawned
void ATutorialNotify::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger->SetBoxExtent(FVector(194.383270, 200.163177,  152.044571));
	
}

void ATutorialNotify::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnActorBeginOverlap.AddDynamic(this, &ATutorialNotify::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATutorialNotify::OnOverlapEnd);
	
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
	
	auto Player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!Player)return;

	auto Controller = Cast<AEGPlayerController>(Player->GetController());
	if (!Controller)return;
	
	
	
	
}

void ATutorialNotify::OnOverlapEnd(AActor * OvelappedActor, AActor * OtherActor)
{
	auto Player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!Player)return;
	auto Controller = Cast<AEGPlayerController>(Player->GetController());
	if (!Controller)return;

	//띄워준 ui를 화면에서 지워야 된다
	

	
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

void ATutorialNotify::loadTutorialMessage(AEGPlayerController* PlayerController)
{
	if (!PlayerController)
	{
		EGLOG(Error, TEXT("Player Controller is nullptr"));
		return;

	}
	auto NotifyName = ATutorialNotify::SetOfTypesOfNotifications.Find(NotifyType);
	PlayerController->LoadTutorialMessage(NotifyName,bIsImportant);


}








