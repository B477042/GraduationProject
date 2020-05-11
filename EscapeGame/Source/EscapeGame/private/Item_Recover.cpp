// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Recover.h"
#include "EGPlayerCharacter.h"

AItem_Recover::AItem_Recover()
{
	amount_Recover = 40;
	loadAsset();
}

void AItem_Recover::BePickedUp(ACharacter * OtherActor)
{
	Super::BePickedUp(OtherActor);


}

void AItem_Recover::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Body->OnComponentBeginOverlap.AddDynamic(this, &AItem_Recover::OnPlayerOverlap);
	//Body->collision
}

void AItem_Recover::useMe()
{

}

void AItem_Recover::OnPlayerOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	//게임에서 표시되지 않고 overlap이벤트도 꺼준다
	Body->SetCollisionProfileName(FName("No collision"));
	SetActorHiddenInGame(true);
	Body->SetGenerateOverlapEvents(false);

	//여기서 아이템을 player에게 넘겨준다


}

void AItem_Recover::loadAsset()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BODY(TEXT("StaticMesh'/Game/MyFolder/Download_Object/Sci-fi_battery.Sci-fi_battery'"));
	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh(  SM_BODY.Object);
		Body->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
		Body->SetWorldRotation(FRotator(0.0f, 0.0f, 90.0f));
		Body->SetCollisionProfileName(FName("OnTrapTrigger"));
		//Body->bGenerateOverlapEvents = true;

	}
	
}
