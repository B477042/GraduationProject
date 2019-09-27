// Fill out your copyright notice in the Description page of Project Settings.

#include "OneSideBlockedPath.h"

// Sets default values
AOneSideBlockedPath::AOneSideBlockedPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// UPROPERTY ��� ���� �ʱ�ȭ
	Plate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PLATE")); 
	MiddleWall = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MIDDLEWALL"));
	Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CEILING"));
	LampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LAMPMESH"));

	LampLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("LAMPLIGHT"));


	//���� �ε�
	//�ٴ�
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_PLATE(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_FloorPanel_A_2.SM_FloorPanel_A_2"));
	if (SM_PLATE.Succeeded())
	{
		Plate->SetStaticMesh(SM_PLATE.Object);
	}
	
	//�ߺ�
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MIDDLE(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Wall_A_2.SM_Wall_A_2"));
	if (SM_MIDDLE.Succeeded())
	{
		MiddleWall->SetStaticMesh(SM_MIDDLE.Object);
	}


	//õ��

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_CEILING(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Ceiling_B_4.SM_Ceiling_B_4"));
	if (SM_CEILING.Object)
	{
		Ceiling->SetStaticMesh(SM_CEILING.Object);
	}
	//���

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_LAMPMESH(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Light_Square.SM_Light_Square"));
	if (SM_LAMPMESH.Succeeded())
	{
		LampMesh->SetStaticMesh(SM_LAMPMESH.Object);
	}





	//Object�� ��ġ ��ġ

	Plate->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//plate->SetRelativeRotation(FRotator(180.0f,90.0f,180.0f));

	
	//MiddleWall->SetRelativeLocation(FVector(-360.0f, 0.0f, 0.0f));
	//MiddleWall->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	Ceiling->SetRelativeLocation(FVector(0.0f, -340.0f, 400.0f));
	Ceiling->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	LampMesh->SetRelativeLocation(FVector(-180.0f, 130.0f - 340.0f, 400.0f));
	LampMesh->SetRelativeRotation(FRotator(180.0f, 90.0f, 00.0f));

	LampLight->SetRelativeLocation(FVector(-190.0f, 120.0f - 340.0f, 400.0f));
	LampLight->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	//SpotLight ��� ����
	LampLight->SetIntensity(47627.695313f);
	LampLight->SetAttenuationRadius(428.286865f);
	LampLight->SetInnerConeAngle(21.464767f);
	LampLight->SetOuterConeAngle(28.952377f);
	//���� �������� ���� Light�� Static����
	LampLight->SetMobility(EComponentMobility::Movable);


	//UPROPERTY �������� �����
	RootComponent = Plate;
	MiddleWall->SetupAttachment(Plate);
	Ceiling->SetupAttachment(Plate);
	LampMesh->SetupAttachment(Plate);;

	LampLight->SetupAttachment(Plate);


}

// Called when the game starts or when spawned
void AOneSideBlockedPath::BeginPlay()
{
	Super::BeginPlay();
	
}

//
//// Called every frame
//void AOneSideBlockedPath::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
