// Fill out your copyright notice in the Description page of Project Settings.


#include "DecoActor/NormalPath.h"

#include "EscapeGame.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameSystem/MiniMap/MiniMapMarkerComponent.h"
// Sets default values
ANormalPath::ANormalPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//2019 09 26 ���� Tick�� �ʿ� ����
	PrimaryActorTick.bCanEverTick = false;
	// UPROPERTY ��� ���� �ʱ�ȭ
	Plate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PLATE"));
	LeftSideWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEFTSIDEWALL"));
	RightSideWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIGHTSIDEWALL"));
	Ceiling =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CEILING"));
	LampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LAMPMESH"));

	LampLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("LAMPLIGHT"));


	//���� �ε�
	//�ٴ�
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_PLATE(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_FloorPanel_A_2.SM_FloorPanel_A_2"));
	if (SM_PLATE.Succeeded())
	{
		Plate->SetStaticMesh(SM_PLATE.Object);
	}
	//�캮



	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_LEFT(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Wall_A_2.SM_Wall_A_2"));
	if (SM_LEFT.Succeeded())
	{
		LeftSideWall->SetStaticMesh(SM_LEFT.Object);
	}
	//�º�
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_RIGHT(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Wall_A_2.SM_Wall_A_2"));
	if (SM_RIGHT.Succeeded())
	{
		RightSideWall->SetStaticMesh(SM_RIGHT.Object);
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

	LeftSideWall->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
	
	RightSideWall->SetRelativeLocation(FVector(-330.0f, -360.0f, 0.0f));
	RightSideWall->SetRelativeRotation(FRotator(0.0f, -180.0f, 0.0f));

	
	Ceiling->SetRelativeLocation(FVector(0.0f, -360.0f, 410.0f));
	Ceiling->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	
	
	LampMesh->SetRelativeLocation(FVector(-170.0f, -150, 410.0f));
	LampMesh->SetRelativeScale3D(FVector(1.5f, 1.0f, 1.0f));

 
	LampLight->SetRelativeLocation(FVector(-160.0f,-180.0f,410.0f));
	LampLight->SetRelativeRotation(FRotator(-90.0f,0.0f,0.0f));
	
//SpotLight ��� ����
	LampLight->SetIntensity(5000.695313f);
	LampLight->SetAttenuationRadius(428.286865f);
	LampLight->SetInnerConeAngle(19.923807f);
	LampLight->SetOuterConeAngle(26.695234f);
	//Mobility
	Plate->SetMobility(EComponentMobility::Stationary);
	LeftSideWall->SetMobility(EComponentMobility::Stationary);
	RightSideWall->SetMobility(EComponentMobility::Stationary);
	Ceiling->SetMobility(EComponentMobility::Stationary);
	LampMesh->SetMobility(EComponentMobility::Stationary);
	LampLight->SetMobility(EComponentMobility::Stationary);



	//UPROPERTY �������� �����
	Plate->SetupAttachment(RootComponent);
	LeftSideWall->SetupAttachment(Plate);
	RightSideWall->SetupAttachment(Plate);
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
void ANormalPath::BeginPlay()
{
	Super::BeginPlay();
	
}
