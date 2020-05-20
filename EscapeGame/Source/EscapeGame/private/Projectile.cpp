// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "EnemyCharacter.h"
#include "EGPlayerCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	initComponents();
	bIsFire = false;
	FireDir = FVector::ZeroVector;
	SetActorLocation(FVector::ZeroVector);
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
	SoundHit->OnAudioFinished.AddDynamic(this, &AProjectile::setSafety);

}

void AProjectile::OnSomethingHit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	FDamageEvent damageEvent;
	auto isPawn = Cast<APawn>(OtherActor);
	if (GetWorld()->GetFirstPlayerController() && isPawn != nullptr)
	{
		OtherActor->TakeDamage(Damage, damageEvent, GetWorld()->GetFirstPlayerController(), this);
	}
	ActivateEffect();
}

void AProjectile::OnCharacterEntered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SoundPassing->Play();
}

void AProjectile::ActivateEffect()
{
	MainEffect->Deactivate();
	HitEffect->SetHiddenInGame(false);
	HitEffect->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	setSafety();
}

void AProjectile::setSafety()
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

void AProjectile::gliding()
{
	if (!bIsFire)return;
	FVector NewLocation = GetActorLocation() + (FireDir*Acceleration);
	SetActorLocation(NewLocation);

}

void AProjectile::initComponents()
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

	Root->SetHiddenInGame(true);
	Collision->SetCollisionProfileName(TEXT("NoCollision"));
	SoundTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	
	SoundHit->bAutoActivate = false;
	SoundPassing->bAutoActivate = false;
	MainEffect->SetHiddenInGame(true);
	ReactEffect->SetHiddenInGame(true);
	ReactEffect->bAutoActivate = false;
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	gliding();
}

