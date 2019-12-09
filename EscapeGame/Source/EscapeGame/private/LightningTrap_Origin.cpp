// Fill out your copyright notice in the Description page of Project Settings.

#include "LightningTrap_Origin.h"

// Sets default values
ALightningTrap_Origin::ALightningTrap_Origin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Timer = 0.0f;
	ActveTime = 3.0f;
	IntervalTime = 2.0f;
	Damage = 5.0f;
	KnockBackRange = 50.0f;
	bIsActive = true;
	initComponents();
}

// Called when the game starts or when spawned
void ALightningTrap_Origin::BeginPlay()
{
	Super::BeginPlay();
	//CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this,&ALightningTrap_Origin::OnCharacterOverlap);
	CapsuleCollision->OnComponentHit.AddDynamic(this,&ALightningTrap_Origin::OnCharacterHit);
	Effect->OnSystemFinished.AddDynamic(this,&ALightningTrap_Origin::StopPlay);
	//Effect->OnSystemPreActivationChange.AddDynamic(this, &ALightningTrap_Origin::StopPlay);
}

// Called every frame
void ALightningTrap_Origin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;
	/*EGLOG(Warning, TEXT("Tick~: %f"), DeltaTime);
	EGLOG(Warning, TEXT("Timer : %f"), Timer);*/
	//번개 함정이 켜졌을 경우
	//active Time을 넘겼을 경우, 함정을 꺼준다
	if (bIsActive)
	{
		if (Timer < ActveTime)return;
		turnOffTrap();
	}
	//번개가 함정이 꺼졌을 경우
	//interval time을 넘겼을 경우, 함정을 켜준다
	else
	{
		if (Timer < IntervalTime)return;
		turnOnTrap();
	}

}

bool ALightningTrap_Origin::IsActive()
{
	return bIsActive;
}

void ALightningTrap_Origin::initComponents()
{
	MeshA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESHA"));
	MeshB = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESHB"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	CapsuleCollision = CreateDefaultSubobject <UCapsuleComponent>(TEXT("CAPSULE"));
	SparkAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("SPARKAUDIO"));

	 RootComponent = MeshA;
	
	 MeshB->SetupAttachment(RootComponent);
	 Effect->SetupAttachment(RootComponent);
	 CapsuleCollision->SetupAttachment(RootComponent);
	 SparkAudio->SetupAttachment(CapsuleCollision);
	// Effect->bAutoActivate = false;


	 //Call other funcs to init components
	 loadAssets();
	 setRelativeCoordinates();
	 setupCollision();

}

void ALightningTrap_Origin::loadAssets()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("StaticMesh'/Game/StarterBundle/ModularScifiProps/Meshes/SM_Coaster.SM_Coaster'"));
	if (SM_MESH.Succeeded())
	{
		MeshA->SetStaticMesh(SM_MESH.Object);
		MeshB->SetStaticMesh(SM_MESH.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem >PS_EFFECT(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_Beam.P_Beam'"));
	if(PS_EFFECT.Succeeded())
	{
		Effect->SetTemplate(PS_EFFECT.Object);
	}

	//SoundWave'/Game/MagicModule/SFX/WAV/WAV_LightingSparks.WAV_LightingSparks'
	static ConstructorHelpers::FObjectFinder<USoundBase>SB_SPARK(TEXT("SoundWave'/Game/MagicModule/SFX/WAV/WAV_LightingSparks.WAV_LightingSparks'"));
	if (SB_SPARK.Succeeded())
	{
		SparkAudio->SetSound(SB_SPARK.Object);

	}
	SparkAudio->bAutoActivate = false;
	Effect->bAutoActivate = false;
	//SoundAttenuation'/Game/MyFolder/Sound/SparkAttenuation.SparkAttenuation'
	static ConstructorHelpers::FObjectFinder <USoundAttenuation>SA_SPARK(TEXT("SoundAttenuation'/Game/MyFolder/Sound/SparkAttenuation.SparkAttenuation'"));
	if (SA_SPARK.Succeeded())
	{
		SparkAudio->AttenuationSettings = SA_SPARK.Object;
	}
}

void ALightningTrap_Origin::setRelativeCoordinates()
{
	float X=0.0f, Y=0.0f, Z=0.0f, Yaw=0.0f, Pitch=0.0f, Roll=0.0f;
	//(X = -20.000000, Y = -290.000000, Z = 150.000000)
	//MeshA->SetRelativeLocation(FVector(X = -310.000000f, Y = -290.000000f, Z = 150.000000f));
	MeshA->SetRelativeRotation(FRotator(Pitch = -90.000000f, Yaw = 0.000000f, Roll = 90.000000f));

	MeshB->SetRelativeLocation(FVector(X = 00.000000f, Y = 0.000000f, Z = 300.000000f));
	//MeshB->SetRelativeRotation(FRotator(Pitch = 280.000092, Yaw = 360.000000, Roll = 360.000122));
	
	Effect->SetRelativeScale3D(FVector(X = 0.600000f, Y = 1.000000f, Z = 1.000000f));
	Effect->SetRelativeRotation(FRotator(Pitch = 90.000000f, Yaw = 0.000000f, Roll = -90.000000f));
	//Effect->SetRelativeRotation(FRotator(Pitch = -0.000519, Yaw = 360.000000, Roll = 360.000000));
	
	CapsuleCollision->SetRelativeLocation(FVector(X = -0.000092, Y = -0.000318, Z = 149.999588));
	
	
}

void ALightningTrap_Origin::setupCollision()
{
	CapsuleCollision->SetCapsuleRadius(20.0f);
	CapsuleCollision->SetCapsuleHalfHeight(148.273148f);
	CapsuleCollision->SetCollisionProfileName(TEXT("NoCollision"));
	CapsuleCollision->SetGenerateOverlapEvents(true);
}

void ALightningTrap_Origin::StopPlay(class UParticleSystemComponent* PSystem)
{
	SparkAudio->Stop();
	EGLOG(Warning, TEXT("Stop"));
}

void ALightningTrap_Origin::turnOnTrap()
{
//	EGLOG(Error, TEXT("Turn on"));
	Effect->Activate();
	SparkAudio->Play();
	CapsuleCollision->SetCollisionProfileName(TEXT("OnBlockingTypeTrap"));
	Timer = 0.0f;
	bIsActive = true;
	
}

void ALightningTrap_Origin::turnOffTrap()
{
	//EGLOG(Error, TEXT("Turn off"));
	CapsuleCollision->SetCollisionProfileName(TEXT("NoCollision"));
	Effect->DeactivateSystem();
	
	//SparkAudio->Stop();
	//SparkAudio->Deactivate();
	Timer = 0.0f;
	bIsActive = false;
}



void ALightningTrap_Origin::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	EGLOG(Error, TEXT("Overlap Actor : %s"),* OtherActor->GetName());
	OtherActor->TakeDamage(Damage, ActorTakeDamageEvent, OtherActor->GetInstigatorController(), this);
	
	/*auto newPos = OtherActor->GetActorLocation() - OtherActor->GetActorForwardVector()*KnockBackRange;
	OtherActor->SetActorLocation(newPos);*/

}

void ALightningTrap_Origin::OnCharacterHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	EGLOG(Error, TEXT("Hit Actor : %s"), *OtherActor->GetName());
	OtherActor->TakeDamage(Damage, ActorTakeDamageEvent, OtherActor->GetInstigatorController(), this);
}

