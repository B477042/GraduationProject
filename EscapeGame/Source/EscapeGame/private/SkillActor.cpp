// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor.h"

// Sets default values
ASkillActor::ASkillActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	initComponents();
	
	SetActorLocation(FVector::ZeroVector);

	Damage = 0.0f;
}

void ASkillActor::ActivateMainEffect()
{
	VFX_Main->Activate();
	
}
void ASkillActor::ActivateHitEffect()
{
	VFX_Main->Deactivate();
	VFX_Hit->SetHiddenInGame(false);
	VFX_Hit->Activate();
	SFX_Hit->Play();
	MainCollision->SetCollisionProfileName(TEXT("NoCollision"));
	
	SetSafety(VFX_Hit);

}


// Called when the game starts or when spawned
void ASkillActor::BeginPlay()
{
	Super::BeginPlay();
	SetSafety(nullptr);
}

void ASkillActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASkillActor::SetSafety(UParticleSystemComponent* PSystem)
{

	
	Root->SetHiddenInGame(true);
	
	MainCollision->SetCollisionProfileName(TEXT("NoCollision"));
	

	SFX_Hit->bAutoActivate = false;
	SFX_Passing->bAutoActivate = false;
	VFX_Main->SetHiddenInGame(true);
	//ReactEffect->SetHiddenInGame(true);
	//ReactEffect->bAutoActivate = false;

	SFX_Hit->Deactivate();
	SFX_Passing->Deactivate();
	
}

void ASkillActor::initComponents()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	VFX_Main = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MainVFX"));
//	ReactEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ReactEffect"));
	VFX_Hit = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitVFX"));
	MainCollision = CreateDefaultSubobject<USphereComponent>(TEXT("COLLISION"));
	
	SFX_Passing = CreateDefaultSubobject<UAudioComponent >(TEXT("SOUNDPassing"));
	SFX_Hit = CreateDefaultSubobject<UAudioComponent >(TEXT("SOUNDHit"));

	RootComponent = Root;
	MainCollision->SetupAttachment(RootComponent);
	VFX_Main->SetupAttachment(RootComponent);
	//ReactEffect->SetupAttachment(RootComponent);
	VFX_Hit->SetupAttachment(RootComponent);
	VFX_Main->SetupAttachment(RootComponent);
	SFX_Passing->SetupAttachment(RootComponent);
	SFX_Hit->SetupAttachment(RootComponent);


	//Root->SetHiddenInGame(true);
	MainCollision->SetCollisionProfileName(TEXT("NoCollision"));

	
	SFX_Hit->bAutoActivate = false;
	SFX_Passing->bAutoActivate = false;
	//MainEffect->SetHiddenInGame(true);
	//ReactEffect->SetHiddenInGame(true);
	//ReactEffect->bAutoActivate = false;
}

// Called every frame
void ASkillActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

