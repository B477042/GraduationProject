// Fill out your copyright notice in the Description page of Project Settings.

#include "HPBox.h"
#include"EGPlayerCharacter.h"

// Sets default values
AHPBox::AHPBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsOpened = false;

	
	initComponents();
	loadAssets();
	setupCollision();

}

// Called when the game starts or when spawned
void AHPBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHPBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AHPBox::OnCharacterOverlap);
}

// Called every frame
void AHPBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHPBox::loadAssets()
{
	//StaticMesh'/Game/StarterBundle/ModularScifiHallways/Meshes/SM_Crate_A.SM_Crate_A' - closed
	//StaticMesh'/Game/StarterBundle/ModularScifiHallways/Meshes/SM_Crate_A3.SM_Crate_A3' - opened
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_CLOSEBOX(TEXT("/Game/StarterBundle/ModularScifiHallways/Meshes/SM_Crate_A.SM_Crate_A"));
	if (SM_CLOSEBOX.Succeeded())
	{
		EGLOG(Warning, TEXT("Box1 added"));
		MeshArray.Add(SM_CLOSEBOX.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_OPENBOX(TEXT("/Game/StarterBundle/ModularScifiHallways/Meshes/SM_Crate_A3.SM_Crate_A3"));
	if (SM_OPENBOX.Succeeded())
	{
		EGLOG(Warning, TEXT("Box2 added"));
		MeshArray.Add(SM_OPENBOX.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>U_EFFECT(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_Healing.P_Healing'"));
	if (U_EFFECT.Succeeded())
	{
		Effect->SetTemplate(U_EFFECT.Object);
		Effect->bAutoActivate = false;
		
	}
	
 
	Body->SetStaticMesh(*MeshArray.GetData());
}

void AHPBox::initComponents()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject <UParticleSystemComponent >(TEXT("EFFECT"));



	RootComponent = Body;
	
	
	BoxCollider->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);
	
}

void AHPBox::setupCollision()
{
	BoxCollider->SetCollisionProfileName(TEXT("ItemBox"));
	Body->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollider->SetGenerateOverlapEvents(true);

	FVector temp = new FVector(float X = 38.219345f, float Y = 49.518700f, float Z = 39.436543f);
	BoxCollider->SetBoxExtent();
}

void AHPBox::switchMesh(UParticleSystemComponent*PSystem)
{
	Effect->Activate(false);
	auto it = MeshArray.CreateIterator();
	it++;
	Body->SetStaticMesh(*it);
}



void AHPBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Player = Cast<AEGPlayerCharacter>(OtherActor);
	if (Player == nullptr)return;
	Player->GetStatComponent()->HealHP(20.0f);
	Body->bHiddenInGame = true;
	Effect->Activate(true);
	SetActorEnableCollision(false);

	Effect->OnSystemFinished.AddDynamic(this, &AHPBox::switchMesh );
	
}

