// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "EnemyCharacter.h"
#include "EGPlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "EGGameInstance.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	
	Acceleration = 10.5f;
	
	Trigger_Passing = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger_Passing"));
	Trigger_Passing->SetupAttachment(RootComponent);
	Trigger_Passing->SetCollisionProfileName(TEXT("NoCollision"));

	bIsFired = false;
	FireDir = FVector::ZeroVector;


	Trigger_Passing->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	Trigger_Passing->SetSphereRadius(200.0f);
	MainCollision->SetSphereRadius(40.3f);
	
	bIsDebugMode = false;
	//initComponents();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//EGLOG(Warning, TEXT("d"));
	gliding();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//SetSafety();

	auto gameInstance = Cast<UEGGameInstance>(GetGameInstance());
	if (!gameInstance)
	{
		bIsDebugMode = gameInstance->bIsDebugMode;
	}

}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MainCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnSomethingHit);

	Trigger_Passing->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnPlayerEntered);;
	

	//VFX_Hit->OnSystemFinished.AddDynamic(this, &ASkillActor::SetSafety);

}



void AProjectile::ReadyToFire(const FVector & Dir_Vector, const FVector& Location, const FRotator& Rotate)
{
	FireDir = Dir_Vector;
	SetActorHiddenInGame(false);
	Root->SetHiddenInGame(false);
	VFX_Main->SetHiddenInGame(false);
	VFX_Hit->SetHiddenInGame(true);
	//SFX_Passing->SetCollisionProfileName("OnTrapTrigger");

	

	
	SetActorLocationAndRotation(Location, Rotate);
	
	MainCollision->SetCollisionProfileName("EnemyWeapon");
	
	fire();
}

void AProjectile::fire()
{
	bIsFired = true;
	//EGLOG(Error, TEXT("Free fire"));
	VFX_Main->Activate();

}


void AProjectile::SetSafety(UParticleSystemComponent* PSystem)
{
	Super::SetSafety(PSystem);

	FireDir = FVector::ZeroVector;
	Trigger_Passing->SetCollisionProfileName(TEXT("NoCollision"));
}

void AProjectile::ActivateHitEffect()
{
	Super::ActivateHitEffect();
	bIsFired = false;
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

	EGLOG(Error, TEXT(" Hit : %s"), *OtherActor->GetName());

	//bIsFired = false;
}

void AProjectile::Reflected()
{
	////Turn 180 Degrees
	//FRotator CurrentRotation = GetActorRotation();
	//FVector ReflectPos = GetActorLocation() - GetActorForwardVector() * 20;
	//float NewYaw = FMath::RandRange(120, 210);
	//float NewRoll = FMath::RandRange(120, 210);
	//
	//
	////Set Safty
	//SetSafety(nullptr);
	//
	//FRotator NewRotation = CurrentRotation+FRotator(0,NewYaw,NewRoll);
	//SetActorRotation(NewRotation);
	//
	//MainCollision->SetCollisionProfileName("PlayerWeapon");
	//fire();
	//
	//EGLOG(Warning, TEXT("Reflected "));
}

void AProjectile::OnPlayerEntered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if(!player)
	{
		
		
		SFX_Passing->Play();
	}

}
 

void AProjectile::gliding()
{
	if (!bIsFired)return;
	//EGLOG(Error, TEXT("Gliding"));
	FVector NewLocation = GetActorLocation() + (FireDir*Acceleration);
	SetActorLocation(NewLocation);

}


