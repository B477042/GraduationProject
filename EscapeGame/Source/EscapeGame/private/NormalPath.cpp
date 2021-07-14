// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalPath.h"

// Sets default values
ANormalPath::ANormalPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//2019 09 26 아직 Tick은 필요 없다
	PrimaryActorTick.bCanEverTick = false;
	// UPROPERTY 멤버 변수 초기화
	Plate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PLATE"));
	LeftSideWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEFTSIDEWALL"));
	RightSideWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIGHTSIDEWALL"));
	Ceiling =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CEILING"));
	LampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LAMPMESH"));

	LampLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("LAMPLIGHT"));


	//에셋 로드
	//바닥
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_PLATE(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_FloorPanel_A_2.SM_FloorPanel_A_2"));
	if (SM_PLATE.Succeeded())
	{
		Plate->SetStaticMesh(SM_PLATE.Object);
	}
	//우벽



	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_LEFT(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Wall_A_2.SM_Wall_A_2"));
	if (SM_LEFT.Succeeded())
	{
		LeftSideWall->SetStaticMesh(SM_LEFT.Object);
	}
	//좌벽
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_RIGHT(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Wall_A_2.SM_Wall_A_2"));
	if (SM_RIGHT.Succeeded())
	{
		RightSideWall->SetStaticMesh(SM_RIGHT.Object);
	}

	//천장

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_CEILING(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Ceiling_B_4.SM_Ceiling_B_4"));
	if (SM_CEILING.Object)
	{
		Ceiling->SetStaticMesh(SM_CEILING.Object);
	}
	//등불

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_LAMPMESH(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Light_Square.SM_Light_Square"));
	if (SM_LAMPMESH.Succeeded())
	{
		LampMesh->SetStaticMesh(SM_LAMPMESH.Object);
	}





	//Object들 위치 배치
	
	Plate->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Plate->SetMobility(EComponentMobility::Static);

	LeftSideWall->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));
	
	RightSideWall->SetRelativeLocation(FVector(-330.0f, -360.0f, 0.0f));
	RightSideWall->SetRelativeRotation(FRotator(0.0f, -180.0f, 0.0f));

	
	Ceiling->SetRelativeLocation(FVector(0.0f, -360.0f, 410.0f));
	Ceiling->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	
	
	LampMesh->SetRelativeLocation(FVector(-170.0f, -150, 410.0f));
	LampMesh->SetRelativeScale3D(FVector(1.5f, 1.0f, 1.0f));

 
	LampLight->SetRelativeLocation(FVector(-160.0f,-180.0f,410.0f));
	LampLight->SetRelativeRotation(FRotator(-90.0f,0.0f,0.0f));
	
//SpotLight 밝기 조절
	LampLight->SetIntensity(5000.695313f);
	LampLight->SetAttenuationRadius(428.286865f);
	LampLight->SetInnerConeAngle(19.923807f);
	LampLight->SetOuterConeAngle(26.695234f);
	LampLight->SetMobility(EComponentMobility::Stationary);


	//UPROPERTY 계층구조 만들기
	Plate->SetupAttachment(RootComponent);
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
