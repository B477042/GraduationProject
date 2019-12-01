// Fill out your copyright notice in the Description page of Project Settings.

#include "LightningTrap_Origin.h"

// Sets default values
ALightningTrap_Origin::ALightningTrap_Origin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightningTrap_Origin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightningTrap_Origin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightningTrap_Origin::initComponents()
{
	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEFTMESH"));
	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIGHTMESH"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	CapsuleCollision = CreateDefaultSubobject <UCapsuleComponent>(TEXT("CAPSULE"));

	 RootComponent = CapsuleCollision;
	 LeftMesh->SetupAttachment(RootComponent);
	 RightMesh->SetupAttachment(RootComponent);
	 Effect->SetupAttachment(RootComponent);

	 Effect->bAutoActivate = false;
}

void ALightningTrap_Origin::setupMemberVariables()
{
	Timer = 0.0f;
	ActveTimer = 3.0f;
	IntervalTimer = 2.0f;
	bIsActve = false;
}

//void ALightningTrap_Origin::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//}

