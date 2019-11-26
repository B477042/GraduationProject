// Fill out your copyright notice in the Description page of Project Settings.

#include "Claymore.h"
#include"EGPlayerCharacter.h"

AClaymore::AClaymore()
{
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Damage = 40.0f;
	Timer = 0.0f;
	loadAssets();
	setRelativeCoordinates();
	setupCollision();

}



// Called when the game starts or when spawned
void  AClaymore::BeginPlay()
{
	Super::BeginPlay();

	SettingTrap();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AClaymore::ActivateTrap);
}

// Called every frame
void  AClaymore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClaymore::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AClaymore::ActivateTrap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult)
{
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (player == nullptr)return;

	Body->bHiddenInGame = true;
	Effect->Activate(true);
	player->GetStatComponent()->HitDamage(Damage);
	

}


void AClaymore::DeActivateTrap()
{
	
}

void AClaymore::ClearTrap()
{
}

void AClaymore::SettingTrap()
{
	Effect->bHiddenInGame = true;

}

void AClaymore::loadAssets()
{
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BODY(TEXT("/Game/MyFolder/Download_Object/m18a1.m18a1"));
	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh ( SM_BODY.Object);
	}
	//set matrial color
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>Material_BODY(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Materials/Accessories/M_V_Grip_Green.M_V_Grip_Green"));
	if (Material_BODY.Succeeded())
	{
		Body->SetMaterial(0,Material_BODY.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_EFFECT(TEXT("/Game/GrenadePack/Particles/VFX_GrenadeEXP_metal.VFX_GrenadeEXP_metal"));
	if (PS_EFFECT.Succeeded())
	{
		Effect->SetTemplate(PS_EFFECT.Object);
	}


	//Make Components Tree
	RootComponent = Body;
	Effect->SetupAttachment(Body);
	BoxCollision->SetupAttachment(Body);

	Effect->bAutoActivate = false;


}

void AClaymore::setRelativeCoordinates()
{
	if (!Body->GetStaticMesh())return;
	

	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;

	Body->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
	Effect->SetRelativeRotation(FRotator(Pitch = 40.0000f, Yaw = 0.000000f, Roll = 0.000000f));
}

void AClaymore::setupCollision()
{
	
	BoxCollision->SetCollisionProfileName(TEXT("OnStaticTrap"));
	Body->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollision->SetGenerateOverlapEvents(true);


}

void AClaymore::activeTimer()
{
	Timer = 0.3f;
}
