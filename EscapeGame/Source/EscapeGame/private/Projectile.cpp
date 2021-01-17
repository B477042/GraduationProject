// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "EnemyCharacter.h"
#include "EGPlayerCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Acceleration = 10.5f;
	
	Trigger_Passing = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger_Passing"));
	Trigger_Passing->SetupAttachment(RootComponent);
	Trigger_Passing->SetCollisionProfileName(TEXT("NoCollision"));

	bIsFire = false;
	FireDir = FVector::ZeroVector;

	//initComponents();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//EGLOG(Warning, TEXT("d"));
	gliding();
}



void AProjectile::ReadyToFire(const FVector & Dir_Vector, const FVector& Location, const FRotator& Rotate)
{
	FireDir = Dir_Vector;
	SetActorHiddenInGame(false);
	Root->SetHiddenInGame(false);
	VFX_Main->SetHiddenInGame(false);
	VFX_Hit->SetHiddenInGame(true);
	//SFX_Passing->SetCollisionProfileName("OnTrapTrigger");

	

	Trigger_Passing->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	Trigger_Passing->SetSphereRadius(200.0f);

	
	SetActorLocationAndRotation(Location, Rotate);
	MainCollision->SetSphereRadius(40.3f);
	MainCollision->SetCollisionProfileName("EnemyWeapon");
	
	Fire();
}

void AProjectile::Fire()
{
	bIsFire = true;
	//EGLOG(Error, TEXT("Free fire"));
	VFX_Main->Activate();

}


void AProjectile::SetSafety()
{
	Super::SetSafety();

	FireDir = FVector::ZeroVector;
	Trigger_Passing->SetCollisionProfileName(TEXT("NoCollision"));
}

void AProjectile::ActivateHitEffect()
{
	Super::ActivateHitEffect();
	bIsFire = false;
}


void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MainCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnSomethingHit);

	Trigger_Passing->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnCharacterEntered);;
	SFX_Hit->OnAudioFinished.AddDynamic(this, &ASkillActor::SetSafety);

	

}

void AProjectile::OnSomethingHit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	FDamageEvent damageEvent;

	ActivateHitEffect();

	auto isPawn = Cast<APawn>(OtherActor);
	if (GetWorld()->GetFirstPlayerController() && isPawn != nullptr)
	{
		OtherActor->TakeDamage(Damage, damageEvent, GetWorld()->GetFirstPlayerController(), this);
	}

	EGLOG(Error, TEXT(" Hit :%s"), *OtherActor->GetName());

	//bIsFire = false;
}

void AProjectile::Reflected()
{
	

}

void AProjectile::OnCharacterEntered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SFX_Passing->Play();
}

void AProjectile::BP_Fire(FVector  Location, FRotator  Rotation, FVector  Dir)
{
	FireDir = Dir;
	SetActorHiddenInGame(false);
	Root->SetHiddenInGame(false);
	VFX_Main->SetHiddenInGame(false);

	//SFX_Passing->SetCollisionProfileName("OnTrapTrigger");
	MainCollision->SetSphereRadius(40.3f);


	Trigger_Passing->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	Trigger_Passing->SetSphereRadius(200.0f);


	SetActorLocationAndRotation(Location, Rotation);

	MainCollision->SetCollisionProfileName("EnemyWeapon");
	Fire();

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
	//EGLOG(Error, TEXT("Gliding"));
	FVector NewLocation = GetActorLocation() + (FireDir*Acceleration);
	SetActorLocation(NewLocation);

}


