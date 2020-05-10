// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemActor.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	BoxCollision->SetCollisionProfileName(FName("OnTrapTrigger"));

	RootComponent = BoxCollision;
	Effect->SetupAttachment(RootComponent);
	Body->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
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

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnPlayerOverlap);

}

void AItemActor::OnPlayerOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	EGLOG(Warning, TEXT("item overlap test"));
}

void AItemActor::setActorHide()
{
	SetHidden(true);
	BoxCollision->SetCollisionProfileName(FName("NoCollision"));

}

