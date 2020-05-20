// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor.h"

// Sets default values
ASkillActor::ASkillActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	initComponents();
	bIsFire = false;
	FireDir = FVector::ZeroVector;
	SetActorLocation(FVector::ZeroVector);
}

void ASkillActor::ActivateMainEffect()
{
	MainEffect->Activate();
	
}
void ASkillActor::ActivateHitEffect()
{
	MainEffect->Deactivate();
	HitEffect->SetHiddenInGame(false);
	HitEffect->Activate();
}


// Called when the game starts or when spawned
void ASkillActor::BeginPlay()
{
	Super::BeginPlay();
	SetSafety();
}

void ASkillActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASkillActor::SetSafety()
{
	bIsFire = false;
	FireDir = FVector::ZeroVector;

	Root->SetHiddenInGame(true);
	Collision->SetCollisionProfileName(TEXT("NoCollision"));
	SoundTrigger->SetCollisionProfileName(TEXT("NoCollision"));

	SoundHit->bAutoActivate = false;
	SoundPassing->bAutoActivate = false;
	MainEffect->SetHiddenInGame(true);
	ReactEffect->SetHiddenInGame(true);
	ReactEffect->bAutoActivate = false;
}

void ASkillActor::initComponents()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	MainEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FIREBALL"));
	ReactEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ReactEffect"));
	HitEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HIT"));
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("COLLISION"));
	SoundTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SoundTRIGGER"));
	SoundPassing = CreateDefaultSubobject<UAudioComponent >(TEXT("SOUNDPassing"));
	SoundHit = CreateDefaultSubobject<UAudioComponent >(TEXT("SOUNDHit"));

	RootComponent = Root;
	Collision->SetupAttachment(RootComponent);
	MainEffect->SetupAttachment(RootComponent);
	ReactEffect->SetupAttachment(RootComponent);
	HitEffect->SetupAttachment(RootComponent);
	MainEffect->SetupAttachment(RootComponent);
	SoundPassing->SetupAttachment(RootComponent);
	SoundHit->SetupAttachment(RootComponent);
	SoundTrigger->SetupAttachment(RootComponent);

	//Root->SetHiddenInGame(true);
	Collision->SetCollisionProfileName(TEXT("NoCollision"));
	SoundTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	
	SoundHit->bAutoActivate = false;
	SoundPassing->bAutoActivate = false;
	//MainEffect->SetHiddenInGame(true);
	//ReactEffect->SetHiddenInGame(true);
	ReactEffect->bAutoActivate = false;
}

// Called every frame
void ASkillActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

