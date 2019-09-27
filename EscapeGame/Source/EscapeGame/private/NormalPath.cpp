// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalPath.h"

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
	//plate->SetRelativeRotation(FRotator(180.0f,90.0f,180.0f));

	LeftSideWall->SetRelativeLocation(FVector(0.0f, -340.0f, 0.0f));
	LeftSideWall->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	RightSideWall->SetRelativeLocation(FVector(-360.0f, 0.0f, 0.0f));
	RightSideWall->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	Ceiling->SetRelativeLocation(FVector(0.0f, -340.0f, 400.0f));
	Ceiling->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	
	LampMesh->SetRelativeLocation(FVector(-180.0f, 130.0f-340.0f, 400.0f));
	LampMesh->SetRelativeRotation(FRotator(180.0f, 90.0f, 00.0f));

	LampLight->SetRelativeLocation(FVector(-190.0f,120.0f-340.0f,400.0f));
	LampLight->SetRelativeRotation(FRotator(-90.0f,0.0f,0.0f));
//SpotLight ��� ����
	LampLight->SetIntensity(47627.695313f);
	LampLight->SetAttenuationRadius(428.286865f);
	LampLight->SetInnerConeAngle(21.464767f);
	LampLight->SetOuterConeAngle(28.952377f);
	//���� �������� ���� Light�� Static����
	LampLight->SetMobility(EComponentMobility::Movable);


	//UPROPERTY �������� �����
	RootComponent = Plate;
	LeftSideWall->SetupAttachment(Plate);
	RightSideWall->SetupAttachment(Plate);
	Ceiling->SetupAttachment(Plate);
	LampMesh->SetupAttachment(Plate);;

	LampLight->SetupAttachment(Plate);


}

// Called when the game starts or when spawned
void ANormalPath::BeginPlay()
{
	Super::BeginPlay();
	
}

//// Called every frame
//void ANormalPath::Tick(float DeltaTime)
//{
//	//Super::Tick(DeltaTime);
//
//}

