// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrierEffectActor.h"
#include "Materials/MaterialInstance.h"

// Sets default values
ABarrierEffectActor::ABarrierEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EnergySphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnergySphere"));
	WaveSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaveSphere"));

	
	EnergySphere->SetCollisionProfileName(TEXT("NoCollision"));
	WaveSphere->SetCollisionProfileName(TEXT("NoCollision"));
	
	RootComponent = EnergySphere;
	WaveSphere->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SM_Sphere.Succeeded())
	{
		EnergySphere->SetStaticMesh(SM_Sphere.Object);
		WaveSphere->SetStaticMesh(SM_Sphere.Object);

	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_Energy(TEXT("MaterialInstanceConstant'/Game/MyFolder/My_Material/FromKwang/MI_Kwang_Energy_Funnels.MI_Kwang_Energy_Funnels'"));
	if (MI_Energy.Succeeded())
	{
		EnergySphere->SetMaterial(0, MI_Energy.Object);
		
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MI_Wave(TEXT("MaterialInstanceConstant'/Game/MyFolder/My_Material/FromKwang/MI_Kwang_Shockwave.MI_Kwang_Shockwave'"));
	if (MI_Wave.Succeeded())
	{
		WaveSphere->SetMaterial(0, MI_Wave.Object);
	}

	SetActorScale3D(FVector(2.25f, 2.25f, 2.25f));
}

void ABarrierEffectActor::ActivateEffect()
{
	EnergySphere->SetHiddenInGame(false);
	//WaveSphere->SetHiddenInGame(false);

}

void ABarrierEffectActor::DeactivateEffect()
{
	EnergySphere->SetHiddenInGame(true);
	//WaveSphere->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void ABarrierEffectActor::BeginPlay()
{
	Super::BeginPlay();
	EnergySphere->SetHiddenInGame(true);
	//WaveSphere->SetHiddenInGame(true);
}


