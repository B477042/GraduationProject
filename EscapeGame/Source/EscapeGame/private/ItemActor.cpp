// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemActor.h"
#include "EGSaveGame.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	//BoxCollision->SetCollisionProfileName(FName("OnTrapTrigger"));

	RootComponent = Body;
	//Effect->SetupAttachment(RootComponent);
	//Body->SetupAttachment(RootComponent);
	bIsItemVaild = true;
}



// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bIsItemVaild)
		SetActorDisable();

}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::BePickedUp(ACharacter * OtherActor)
{
	OwnerActor = OtherActor;
	
}

void AItemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnPlayerOverlap);

}

//FName AItemActor::GetTag()
//{
//	return Tag;
//}

void  AItemActor::SetActorDisable()
{
	Body->SetCollisionProfileName("NoCollision");
	SetActorHiddenInGame(true);

}

void AItemActor::SaveGame(UEGSaveGame * SaveInstance)
{
	if (!SaveInstance)
	{
		EGLOG(Error, TEXT("SaveInstance is null"));
		return;
	}
	FItemData ItemData;
	
	

	ItemData.Location = GetActorLocation();
	ItemData.bIsVaild = bIsItemVaild;


}

void LoadGame(UEGSaveGame * LoadInstance)
{
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("LoadInstance is null"));
		return;
	}
}
