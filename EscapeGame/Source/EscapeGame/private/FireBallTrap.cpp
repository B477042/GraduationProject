// Fill out your copyright notice in the Description page of Project Settings.

#include "FireBallTrap.h"

// Sets default values
AFireBallTrap::AFireBallTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	initComponents();
	setupCollision();
}

// Called when the game starts or when spawned
void AFireBallTrap::BeginPlay()
{
	Super::BeginPlay();
	FireBall = GetWorld()->SpawnActor <AFireBallActor>();
	FireBall->SetActorHiddenInGame(true);
	FireBall->AttachToComponent(FirePoint, FAttachmentTransformRules::KeepRelativeTransform);
}

void AFireBallTrap::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AFireBallTrap::OnPlayerEntered);
}

// Called every frame
void AFireBallTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AFireBallTrap::initComponents()
{
	Root= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	FirePoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FIREPOINT"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	RootComponent = Root;
	FirePoint->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(RootComponent);
	
	FirePoint->SetRelativeLocation(FVector(0.0f,600.0f, 90.0f));
	FirePoint->SetRelativeRotation(FRotator(0.000000f, 270.0f, 0.000000f));

	//StaticMesh'/Game/StarterBundle/ModularScifiProps/Meshes/SM_Coaster.SM_Coaster'
	static ConstructorHelpers::FObjectFinder <UStaticMesh>SM_Mesh(TEXT("StaticMesh'/Game/StarterBundle/ModularScifiProps/Meshes/SM_Coaster.SM_Coaster'"));
	if (SM_Mesh.Succeeded())
	{
		Root->SetStaticMesh(SM_Mesh.Object);
	}
}

void AFireBallTrap::setupCollision()
{
	Trigger->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	Trigger->SetBoxExtent(FVector(150.000000f, 70.000000f, 67.991219f));
	Trigger->SetGenerateOverlapEvents(true);
}

void AFireBallTrap::Fire()
{
	FireBall->Fire();
	Trigger->SetCollisionProfileName(TEXT("NoCollision"));
	FireBall.Get();
	Destroy();
}

void AFireBallTrap::OnPlayerEntered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FireBall->SetActorHiddenInGame(false);
	Fire();
	
}

