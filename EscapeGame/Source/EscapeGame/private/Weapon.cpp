// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "EGPlayerCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	initComponents();

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	Effect->bAutoActivate = false;

}
void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	AttackRangeBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnActorBeginOverlap);

}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AWeapon::GetDamage()
{
	return Damage;
}

void AWeapon::EquipTo(ACharacter * OtherActor)
{
	OwnerChara = OtherActor;
}

void AWeapon::initComponents()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	AttackRangeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOXCOMP"));
	RootComponent = AttackRangeBox;
	Effect->SetupAttachment(RootComponent);
	Body->SetupAttachment(RootComponent);
	Damage = 10;

}

void AWeapon::OnActorBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//EGLOG(Error, TEXT("Hi Master"));
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!player) { return; }
	Effect->Activate();
	
}


void AWeapon::initBodyCollision()
{
	if (!Body->GetStaticMesh())return;

	Body->SetCollisionProfileName(TEXT("PlayerWeapon"));
	

}

