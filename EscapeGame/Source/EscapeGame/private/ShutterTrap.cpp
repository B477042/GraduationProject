// Fill out your copyright notice in the Description page of Project Settings.

#include "ShutterTrap.h"
#include "EGPlayerCharacter.h"

// Sets default values
AShutterTrap::AShutterTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsActivated = false;
	Timer = 0.0f;
	initComponents();
	loadAssets();
	setupCollision();

}

// Called when the game starts or when spawned
void AShutterTrap::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < n_spears; i++)
	{
		Spears.Emplace(GetWorld()->SpawnActor<ASpearActor>());
		if (Spears[i].IsValid())
		{
			
			Spears[i]->SetActorHiddenInGame(true);
			FVector location = Root->GetComponentLocation() + FVector(100.0f - (50.0f*i), -10.0f, -120.0f);
			Spears[i]->SetActorRelativeLocation(location);
			Spears[i]->SetCollisionProfileTo(TEXT("NoCollision"));
		}
		
	}
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AShutterTrap::OnPlayerEntered);
}

// Called every frame
void AShutterTrap::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if (!bIsActivated)return;

	Timer += DeltaTime;
	if (Timer <= StreachTime)
	{
		RiseUpSpears(DeltaTime);
	}
	else
	{
		
		PrimaryActorTick.bCanEverTick = false;
		bIsActivated = false;
		SoundEffect->Stop();
		EGLOG(Error, TEXT("Tick"));
	}
}

void AShutterTrap::RiseUpSpears(float deltaTime)
{
	float newZ=(spear_last-spear_start)/StreachTime*deltaTime;
	for (int i = 0; i < n_spears; i++)
	{
		FVector spearPos = Spears[i]->GetActorLocation();
		EGLOG(Warning, TEXT("Rise!"));
		FVector newLocation = spearPos + FVector(0.0f, 0.0f, newZ);
		Spears[i]->SetActorLocation(newLocation);
	}

}

void AShutterTrap::OnPlayerEntered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (auto Player = Cast<AEGPlayerCharacter>(OtherActor) == nullptr)
		return;
	//Activate Tick 
	//PrimaryActorTick.bCanEverTick = true;
	for (int i=0;i<n_spears;i++)
	{
		Spears[i]->SetActorHiddenInGame(false);
		Spears[i]->SetCollisionProfileTo(TEXT("OnBlockingTypeTrap"));
	}
	SoundEffect->Play();
	bIsActivated = true;
	Trigger->SetCollisionProfileName(TEXT("NoCollision"));
}

void AShutterTrap::initComponents()
{
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ROOT"));
	SoundEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("SE"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	RootComponent = Root;
	SoundEffect->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(RootComponent);
	
	float X, Y, Z;
	Trigger->SetRelativeLocation(FVector(X = 0.000000f, Y = -680.000000f, Z = 90.000000f));

	

}

void AShutterTrap::loadAssets()
{
	static ConstructorHelpers::FObjectFinder<USoundBase>SB_SOUND(TEXT("SoundWave'/Game/MyFolder/Sound/unsheath-sword.unsheath-sword'"));
	if (SB_SOUND.Succeeded())
	{
		SoundEffect->SetSound(SB_SOUND.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundAttenuation>SA_ATTENUATION(TEXT("SoundAttenuation'/Game/MyFolder/Sound/SparkAttenuation.SparkAttenuation'"));
	if(SA_ATTENUATION.Succeeded())
	{
		SoundEffect->AttenuationSettings = SA_ATTENUATION.Object;
	}

}

void AShutterTrap::setupCollision()
{
	Trigger->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	Trigger->SetBoxExtent(FVector(150.000000f, 70.000000f, 67.991219f));
	Trigger->SetGenerateOverlapEvents(true);
}

