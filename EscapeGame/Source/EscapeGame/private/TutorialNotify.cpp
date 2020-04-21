// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialNotify.h"
#include "EGPlayerController.h"
#include "EGPlayerCharacter.h"

// Sets default values
ATutorialNotify::ATutorialNotify()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	
	NotifyType = ENotifyType::E_None;

	//GetCollisionComponent()->extent
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
}

void ATutorialNotify::OnOverlapEnd(AActor * OvelappedActor, AActor * OtherActor)
{
	if (!checkOverlappedActor((OtherActor)))return;
	EGLOG(Warning, TEXT("Goodbye player"));
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

