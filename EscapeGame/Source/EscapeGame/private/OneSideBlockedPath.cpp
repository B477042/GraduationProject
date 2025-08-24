// Fill out your copyright notice in the Description page of Project Settings.


#include "DecoActor/OneSideBlockedPath.h"

#include "EscapeGame.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameSystem/MiniMap/MiniMapMarkerComponent.h"
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
	Plate->SetMobility(EComponentMobility::Stationary);

	MiddleWall->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
	//LeftSideWall->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	

	//(X=0.000000,Y=-360.000000,Z=410.000000)
	//(Pitch=0.000000,Yaw=0.000000,Roll=0.000000)
	Ceiling->SetRelativeLocation(FVector(0.0f, -360.0f, 410.0f));
	Ceiling->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	//(X=-170.000000,Y=-150.000000,Z=410.000000)
	//(Pitch=0.000000,Yaw=90.000000,Roll=180.000244)
	//(X=1.500000,Y=1.000000,Z=1.000000)
	LampMesh->SetRelativeLocation(FVector(-170.0f, -150, 410.0f));
	//LampMesh->SetRelativeRotation(FRotator(180.0f, 90.0f, 00.0f));
	LampMesh->SetRelativeScale3D(FVector(1.5f, 1.0f, 1.0f));
	//(X=-160.000000,Y=-130.000000,Z=410.000000)
	//(Pitch=-90.000000,Yaw=0.000000,Roll=0.000000)
	LampLight->SetRelativeLocation(FVector(-170.0f, -170.0f, 410.0f));
	LampLight->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	//SpotLight ��� ����
	LampLight->SetIntensity(5000.695313f);
	LampLight->SetAttenuationRadius(428.286865f);
	LampLight->SetInnerConeAngle(18.455242f);
	LampLight->SetOuterConeAngle(22.933331f);
	//Mobility
	Plate->SetMobility(EComponentMobility::Stationary);
	Ceiling->SetMobility(EComponentMobility::Stationary);
	LampMesh->SetMobility(EComponentMobility::Stationary);
	LampLight->SetMobility(EComponentMobility::Stationary);
	MiddleWall->SetMobility(EComponentMobility::Stationary);



	//UPROPERTY �������� �����
	Plate->SetupAttachment(RootComponent);
	MiddleWall->SetupAttachment(Plate);
	Ceiling->SetupAttachment(Plate);
	LampMesh->SetupAttachment(Plate);;
	LampLight->SetupAttachment(Plate);
	//MiniMapTile����
	MiniMapTileMesh->SetRelativeLocation(FVector(-160, -180, POS_Minimap.Z));
	MiniMapTileMesh->SetRelativeScale3D(FVector(3.4375f, 3.8125f, 1.0f));
	/*
*	Trigger Settings
*/
	TileTrigger->SetRelativeLocation(FVector(-150, -180, 220));
	TileTrigger->SetBoxExtent(FVector(181.952499f, 187.690567f, 234.089142f));
}

// Called when the game starts or when spawned
void AOneSideBlockedPath::BeginPlay()
{
	Super::BeginPlay();
	
}

 