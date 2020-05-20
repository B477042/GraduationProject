// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "EnemyCharacter.h"
#include "EGPlayerCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//initComponents();
	
}

void AProjectile::ReadyToFire(const FVector & Dir_Vector, const FVector& Location, const FRotator& Rotate)
{
	FireDir = Dir_Vector;
	Root->SetHiddenInGame(false);
	MainEffect->SetHiddenInGame(false);
	SoundTrigger->SetCollisionProfileName("OnTrapTrigger");
	Collision->SetSphereRadius(40.3f);
	
	SoundTrigger->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	SoundTrigger->SetSphereRadius(200.0f);

	bIsFire = true;
	SetActorLocationAndRotation(Location, Rotate);

}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnSomethingHit);

	SoundTrigger->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnCharacterEntered);;
	SoundHit->OnAudioFinished.AddDynamic(this, &ASkillActor::SetSafety);

}

void AProjectile::OnSomethingHit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	FDamageEvent damageEvent;
	auto isPawn = Cast<APawn>(OtherActor);
	if (GetWorld()->GetFirstPlayerController() && isPawn != nullptr)
	{
		OtherActor->TakeDamage(Damage, damageEvent, GetWorld()->GetFirstPlayerController(), this);
	}
	ActivateHitEffect();
}

void AProjectile::OnCharacterEntered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SoundPassing->Play();
}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//SetSafety();
}



void AProjectile::gliding()
{
	if (!bIsFire)return;
	FVector NewLocation = GetActorLocation() + (FireDir*Acceleration);
	SetActorLocation(NewLocation);

}



// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	gliding();
}

