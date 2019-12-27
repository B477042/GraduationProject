// Fill out your copyright notice in the Description page of Project Settings.

#include "SmokeTrap.h"

// Sets default values
ASmokeTrap::ASmokeTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BC_COLLISION"));

	for (int i = 0; i < n_Smokes; i++)
		Effects.Add(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_EFFECT%i"), i));
	RootComponent = Effects[2];

}

// Called when the game starts or when spawned
void ASmokeTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASmokeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASmokeTrap::OnCharacterEntered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FDamageEvent damageEvent;
	OtherActor->TakeDamage(Damage, damageEvent, GetWorld()->GetFirstPlayerController(), this);
}

