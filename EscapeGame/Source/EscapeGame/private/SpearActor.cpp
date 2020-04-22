// Fill out your copyright notice in the Description page of Project Settings.

#include "SpearActor.h"

// Sets default values
ASpearActor::ASpearActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ROOT"));
	Durability = 10.0f;
	RootComponent = Root;
	Body->SetupAttachment(Root);
	Body->SetRelativeLocation(FVector(0.0f, 0.0f, 65.0f));
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BODY(TEXT("StaticMesh'/Game/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Spear.SM_Spear'"));
	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh(SM_BODY.Object);
	}

	Body->SetCollisionProfileName(TEXT("BlockAll"));

}

void ASpearActor::SetCollisionProfileTo(FName profile)
{
	Body->SetCollisionProfileName(profile);
}

// Called when the game starts or when spawned
void ASpearActor::BeginPlay()
{
	Super::BeginPlay();
	
}

float ASpearActor::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Durability -= DamageAmount;
	if (Durability <= 0.0f)Destroy();

	return DamageAmount;
}

// Called every frame
void ASpearActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

