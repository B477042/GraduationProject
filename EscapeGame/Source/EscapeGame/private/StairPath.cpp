// Fill out your copyright notice in the Description page of Project Settings.


#include "DecoActor/StairPath.h"

#include "EscapeGame.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameSystem/MiniMap/MiniMapMarkerComponent.h"
// Sets default values
AStairPath::AStairPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// UPROPERTY ��� ���� �ʱ�ȭ
	InitUPropertys();
	LoadAssets();
	SettingWorldMatrix();
	MakeComponentsTree();

	/*
	* Trigger Setting
	*/
	TileTrigger->SetRelativeLocation(FVector(90, -130, 210));
	TileTrigger->SetBoxExtent(FVector(285.576141f, 373.145172f, 344.731171f));


	
	LampLight1->SetInnerConeAngle(19.809523f);
	LampLight1->SetOuterConeAngle(25.076189f);
	LampLight1->SetAttenuationRadius(612.470337f);
	LampLight1->SetIntensity(10000.0f);
	
	LampLight2->SetInnerConeAngle(19.809523f);
	LampLight2->SetOuterConeAngle(25.076189f);
	LampLight2->SetAttenuationRadius(612.470337f);
	LampLight2->SetIntensity(10000.0f);


	MiniMapTileMesh->SetRelativeScale3D(FVector(5.75, 7.75, 1));
	MiniMapTileMesh->SetRelativeLocation(FVector(90, -135, POS_Minimap.Z));

	
	Root->SetMobility(EComponentMobility::Stationary);
	Plate1->SetMobility(EComponentMobility::Stationary);
	Plate2->SetMobility(EComponentMobility::Stationary);
	Wall1->SetMobility(EComponentMobility::Stationary);
	Wall2->SetMobility(EComponentMobility::Stationary);
	Wall3->SetMobility(EComponentMobility::Stationary);
	Wall4->SetMobility(EComponentMobility::Stationary);
	Wall5->SetMobility(EComponentMobility::Stationary);
	Stair1->SetMobility(EComponentMobility::Stationary);
	Stair2->SetMobility(EComponentMobility::Stationary);
	Ceiling->SetMobility(EComponentMobility::Stationary);
	CeilingDiv->SetMobility(EComponentMobility::Stationary);
	LampMesh1->SetMobility(EComponentMobility::Stationary);
	LampMesh2->SetMobility(EComponentMobility::Stationary);
	LampLight1->SetMobility(EComponentMobility::Stationary);
	LampLight2->SetMobility(EComponentMobility::Stationary);
}

// Called when the game starts or when spawned
void AStairPath::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStairPath::InitUPropertys()
{
	Plate1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PLATE1"));
	Plate2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PLATE2"));
	Root=  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ROOT"));
	Wall1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL1"));
	Wall2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL2"));
	Wall3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL3"));
	Wall4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL4"));
	Wall5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL5"));

	Stair1= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STAIR1"));
	Stair2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STAIR2"));

	Ceiling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CEILING"));
	CeilingDiv = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CEILINGDIV"));
	LampMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LAMPMESH1"));
	LampMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LAMPMESH2"));

	LampLight1 = CreateDefaultSubobject<USpotLightComponent>(TEXT("LAMPLIGHT1"));
	LampLight2 = CreateDefaultSubobject<USpotLightComponent>(TEXT("LAMPLIGHT2"));

	//Path1 = GetWorld()->SpawnActor<ANormalPath>(ANormalPath::StaticClass());
	//Path2 = GetWorld()->SpawnActor<ANormalPath>(ANormalPath::StaticClass());
}

bool AStairPath::LoadAssets()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_PLATE(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_FloorPanel_A_2.SM_FloorPanel_A_2"));
	if (SM_PLATE.Succeeded())
	{
		Plate1->SetStaticMesh(SM_PLATE.Object);
		Plate2->SetStaticMesh(SM_PLATE.Object);
	}



	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_WALL(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Wall_B_2.SM_Wall_B_2"));
	if (SM_WALL.Succeeded())
	{
		Wall1->SetStaticMesh(SM_WALL.Object);
		Wall2->SetStaticMesh(SM_WALL.Object);
		
		Wall4->SetStaticMesh(SM_WALL.Object);
		Wall5->SetStaticMesh(SM_WALL.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_WALL1(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Wall_B_3.SM_Wall_B_3"));
	if (SM_WALL1.Succeeded())
	{
		Wall3->SetStaticMesh(SM_WALL1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_STAIR(TEXT("/Game/StarterBundle/ModularSci_Comm/Meshes/SM_Stairs_A_Straight.SM_Stairs_A_Straight"));
	if(SM_STAIR.Succeeded())
	{
		Stair1->SetStaticMesh(SM_STAIR.Object);
		Stair2->SetStaticMesh(SM_STAIR.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_CEILING(TEXT("/Game/StarterBundle/ModularScifiProps/Meshes/SM_Ceiling_A.SM_Ceiling_A"));
	if (SM_CEILING.Object)
	{
		Ceiling->SetStaticMesh(SM_CEILING.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_CEILINGDIV(TEXT("/Game/StarterBundle/ModularScifiProps/Meshes/SM_Ceiling_Div_A.SM_Ceiling_Div_A"));
	if (SM_CEILINGDIV.Object)
	{
		CeilingDiv->SetStaticMesh(SM_CEILINGDIV.Object);
	}
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_LAMPMESH(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Light_Square.SM_Light_Square"));
	if (SM_LAMPMESH.Succeeded())
	{
		LampMesh1->SetStaticMesh(SM_LAMPMESH.Object);
		LampMesh2->SetStaticMesh(SM_LAMPMESH.Object);
		Root->SetStaticMesh(SM_LAMPMESH.Object);
	}


	return true;
}

void AStairPath::SettingWorldMatrix()
{
	float X = 0.0f, Y = 0.0f, Z = 0.0f;
	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;

	//Adjust Mesh components Height Value
	float AdjustmentValue = -159;
	Root->SetRelativeLocation(FVector::ZeroVector);

	Plate1->SetRelativeLocation(FVector(X =300.000000f, Y = 190.000000f, Z = 0.000000f+AdjustmentValue));
	Plate1->SetRelativeScale3D(FVector(1.5f, 1.75f, 1.0f));

	Plate2->SetRelativeLocation(FVector(X = 320.000000f, Y = 180.000000f, Z = 160.000000f+AdjustmentValue));
	Plate2->SetRelativeScale3D(FVector(X = 1.000000f, Y = 1.750000f, Z = 1.000000f));

	Wall1->SetRelativeLocation(FVector(X = 320.000000f, Y = -500.000000f, Z = 0.000000f+AdjustmentValue));
	Wall1->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = 0.000000f, Roll = 0.000000f));
	Wall1->SetRelativeScale3D(FVector(X = 1.570000f, Y = 1.000000f, Z = 1.750000f));

	Wall2->SetRelativeLocation(FVector(X = -180.000000f, Y = 250.000000f, Z = 10.000000f+AdjustmentValue));
	Wall2->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = 180.000000f, Roll = 0.000000f));
	Wall2->SetRelativeScale3D(FVector(X = 1.570000f, Y = 1.000000f, Z = 1.750000f));

	Wall3->SetRelativeLocation(FVector(X = 360.000000f, Y = 210.000000f, Z = 0.000000f+AdjustmentValue));
	Wall3->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = 90.000000f, Roll = 0.000000f));
	Wall3->SetRelativeScale3D(FVector(X = 2.250000f, Y = 1.000000f, Z = 1.750000f));

	Wall4->SetRelativeLocation(FVector(X = -230.000000f, Y = -500.000000f, Z = 0.000000f+AdjustmentValue));
	Wall4->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = -90.000000f, Roll = 0.000000f));
	Wall4->SetRelativeScale3D(FVector(X = 1.150000f, Y = 1.000000f, Z = 0.750000f));

	Wall5->SetRelativeLocation(FVector(X = -230.000000f, Y = -130.000000f, Z = 420.000000f+AdjustmentValue));
	Wall5->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = -90.000000f, Roll = 0.000000f));
	Wall5->SetRelativeScale3D(FVector(X = 1.150000f, Y = 1.000000f, Z = 0.750000f));

	Stair1->SetRelativeLocation(FVector(X = 0.000000f, Y = 30.000000f, Z = 0.000000f+AdjustmentValue));
	Stair1->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = 0.000000f, Roll = 0.000000f));
	Stair1->SetRelativeScale3D(FVector(X = 1.000000f, Y = 0.75000f, Z = 1.000000f));

	Stair2->SetRelativeLocation(FVector(X = -170.000f, Y = -300.0000f, Z = 150.000000f+AdjustmentValue));
	Stair2->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = 180.000000f, Roll = 0.000000f));
	Stair2->SetRelativeScale3D(FVector(X = 1.000000f, Y = 0.750000f, Z = 1.000000f));

	Ceiling->SetRelativeLocation(FVector(X = 370.000000f, Y = 200.000000f, Z = 710.000000f+AdjustmentValue));
	Ceiling->SetRelativeRotation(FRotator::ZeroRotator);
	Ceiling->SetRelativeScale3D(FVector(X = 1.750000, Y = 2.000000, Z = 1.000000));

	CeilingDiv->SetRelativeLocation(FVector(X = -180.000000f, Y = -130.000000f, Z = 720.000000f+AdjustmentValue));
	CeilingDiv->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = 90.000000f, Roll = 0.000000f));
	CeilingDiv->SetRelativeScale3D(FVector(X = 1.000000f, Y = 1.000000f, Z = 1.000000f));

	LampMesh1->SetRelativeLocation(FVector(X = -90.000000f, Y = -290.000000f, Z = 690.000000f+AdjustmentValue));
	LampMesh1->SetRelativeRotation(FRotator(Pitch = 180.000000f, Yaw = 90.000000f, Roll = 0.000000f));
	LampMesh1->SetRelativeScale3D(FVector(X = 2.000000f, Y = 2.000000f, Z = 1.000000f));

	LampMesh2->SetRelativeLocation(FVector(X = 314.716888f, Y = 18.943176f, Z = 615.080750f+AdjustmentValue));
	LampMesh2->SetRelativeRotation(FRotator(Pitch = 0.0f,Yaw = 90.0f, Roll = 90.0f));
	LampMesh2->SetRelativeScale3D(FVector(X = 2.000000f, Y = 2.000000f, Z = 1.000000f));

	LampLight1->SetRelativeLocation(FVector(X = 314.716888f, Y = 38.943176f, Z = 595.080750f+AdjustmentValue));
	LampLight1->SetRelativeRotation(FRotator(Pitch = -50.825459, Yaw = 188.736816, Roll = 94.648758));

	LampLight2->SetRelativeLocation(FVector(X = -110.000000f, Y = -320.000000f, Z = 690.000000f+AdjustmentValue));
	LampLight2->SetRelativeRotation(FRotator(Pitch = -67.731102, Yaw = 25.505415, Roll = -27.273155));

	
}

void AStairPath::MakeComponentsTree()
{
	
	//* Before
	Root->SetupAttachment(RootComponent);
	Plate1->SetupAttachment(Root);
	Plate2->SetupAttachment(Root);
	

	/*
	* After 08/18/2021
	*/
	//Plate2->SetupAttachment(RootComponent);
	//Root->SetupAttachment(Plate2);
	//Plate1->SetupAttachment(Root);
	
	
	Wall1->SetupAttachment(Root);
	Wall2->SetupAttachment(Root);
	Wall3->SetupAttachment(Root);
	Wall4->SetupAttachment(Root);
	Wall5->SetupAttachment(Root);

	Stair1->SetupAttachment(Root);
	Stair2->SetupAttachment(Root);

	Ceiling->SetupAttachment(Root);
	CeilingDiv->SetupAttachment(Root);

	LampMesh1->SetupAttachment(Root);
	LampMesh2->SetupAttachment(Root);
	LampLight1->SetupAttachment(Root);
	LampLight2->SetupAttachment(Root);

}

