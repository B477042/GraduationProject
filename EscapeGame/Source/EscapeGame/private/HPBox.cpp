// Fill out your copyright notice in the Description page of Project Settings.

#include "HPBox.h"
#include "EGPlayerCharacter.h"
#include "EGPlayerController.h"
#include "GameWidget.h"

// Sets default values
AHPBox::AHPBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick =false;
	bIsOpened = false;
	Heal = 20.0f;
	BounsTime = 10.0f;

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

float AHPBox::GetBounsTime()
{
	return BounsTime;
}

void AHPBox::loadAssets()
{
	//StaticMesh'/Game/StarterBundle/ModularScifiHallways/Meshes/SM_Crate_A.SM_Crate_A' - closed
	//StaticMesh'/Game/StarterBundle/ModularScifiHallways/Meshes/SM_Crate_A3.SM_Crate_A3' - opened
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_CLOSEBOX(TEXT("/Game/StarterBundle/ModularScifiHallways/Meshes/SM_Crate_A.SM_Crate_A"));
	if (SM_CLOSEBOX.Succeeded())
	{
	//	EGLOG(Warning, TEXT("Box1 added"));
		MeshArray.Add(SM_CLOSEBOX.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_OPENBOX(TEXT("/Game/StarterBundle/ModularScifiHallways/Meshes/SM_Crate_A3.SM_Crate_A3"));
	if (SM_OPENBOX.Succeeded())
	{
	//	EGLOG(Warning, TEXT("Box2 added"));
		MeshArray.Add(SM_OPENBOX.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>U_EFFECT(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_InstantHeal.P_InstantHeal'"));
	if (U_EFFECT.Succeeded())
	{
		Effect->SetTemplate(U_EFFECT.Object);
		Effect->bAutoActivate = false;
		
	}
	static ConstructorHelpers::FObjectFinder<USoundBase>SB_POP(TEXT("SoundWave'/Game/MyFolder/Sound/SE/trashcanOpen_01.trashcanOpen_01'"));
	if (SB_POP.Succeeded())
	{
		PopSound->SetSound(SB_POP.Object);
		PopSound->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<USoundAttenuation>SA_ATTENUATION(TEXT("SoundAttenuation'/Game/MyFolder/Sound/SparkAttenuation.SparkAttenuation'"));
	if (SA_ATTENUATION.Succeeded())
	{
		PopSound->AttenuationSettings = SA_ATTENUATION.Object;
	}
 
	Body->SetStaticMesh(*MeshArray.GetData());
}

void AHPBox::initComponents()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject <UParticleSystemComponent >(TEXT("EFFECT"));
	PopSound = CreateDefaultSubobject<UAudioComponent>(TEXT("POPSOUND"));


	RootComponent = Body;
	
	
	BoxCollider->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);
	PopSound->SetupAttachment(RootComponent);
	
}

void AHPBox::setupCollision()
{
	BoxCollider->SetCollisionProfileName(TEXT("OnItemBox"));
	Body->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollider->SetGenerateOverlapEvents(true);

	BoxCollider->SetRelativeLocation(FVector(40.0f,60.0f,40.0f));
	BoxCollider->SetBoxExtent(FVector( 38.219345f,  49.518700f, 39.436543f));

}

void AHPBox::setBoxStateToOpened()
{
	
		bIsOpened = true;

	
	Effect->Activate(false);

	auto temp = MeshArray.GetData();
	temp++;
	Body->SetStaticMesh(*temp);

	SetActorEnableCollision(true);
	BoxCollider->SetCollisionProfileName("BlockAll");
}



void AHPBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsOpened == true) { 
		//EGLOG(Error, TEXT("opend box"));
		return; 
	}

	auto Player = Cast<AEGPlayerCharacter>(OtherActor);
	if (Player == nullptr)return;

	Player->HealHP(Heal);
	Player->GetTimeLimitComponent()->TimeExtend(BounsTime);

	Effect->Activate(true);
	//EGLOG(Error, TEXT("Collision -> false"));
	SetActorEnableCollision(false);
	PopSound->Play();
	setBoxStateToOpened();
	
	
}

