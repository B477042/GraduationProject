// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalPath.h"

// Sets default values
ANormalPath::ANormalPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//2019 09 26 아직 Tick은 필요 없다
	PrimaryActorTick.bCanEverTick = false;
	// UPROPERTY 멤버 변수 초기화
	plate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PLATE"));
	leftSideWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEFTSIDEWALL"));
	rightSideWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RIGHTSIDEWALL"));
	ceiling =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CEILING"));
	lampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LAMPMESH"));

	lampLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("LAMPLIGHT"));


	//에셋 로드
	//바닥
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_PLATE(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_FloorPanel_A_2.SM_FloorPanel_A_2"));
	if (SM_PLATE.Succeeded())
	{
		plate->SetStaticMesh(SM_PLATE.Object);
	}
	//우벽



	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_LEFT(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Wall_A_2.SM_Wall_A_2"));
	if (SM_LEFT.Succeeded())
	{
		leftSideWall->SetStaticMesh(SM_LEFT.Object);
	}
	//좌벽
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_RIGHT(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Wall_A_2.SM_Wall_A_2"));
	if (SM_RIGHT.Succeeded())
	{
		rightSideWall->SetStaticMesh(SM_RIGHT.Object);
	}

	//천장

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_CEILING(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Ceiling_B_4.SM_Ceiling_B_4"));
	if (SM_CEILING.Object)
	{
		ceiling->SetStaticMesh(SM_CEILING.Object);
	}
	//등불

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_LAMPMESH(TEXT("/Game/StarterBundle/ModularSci_Int/Meshes/SM_Light_Square.SM_Light_Square"));
	if (SM_LAMPMESH.Succeeded())
	{
		lampMesh->SetStaticMesh(SM_LAMPMESH.Object);
	}





	//Object들 위치 배치
	
	plate->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//plate->SetRelativeRotation(FRotator(180.0f,90.0f,180.0f));

	leftSideWall->SetRelativeLocation(FVector(0.0f, -340.0f, 0.0f));
	leftSideWall->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	rightSideWall->SetRelativeLocation(FVector(-360.0f, 0.0f, 0.0f));
	rightSideWall->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	ceiling->SetRelativeLocation(FVector(0.0f, -340.0f, 400.0f));
	ceiling->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	
	lampMesh->SetRelativeLocation(FVector(-180.0f, 130.0f-340.0f, 400.0f));
	lampMesh->SetRelativeRotation(FRotator(180.0f, 90.0f, 00.0f));

	lampLight->SetRelativeLocation(FVector(-190.0f,120.0f-340.0f,400.0f));
	lampLight->SetRelativeRotation(FRotator(-90.0f,0.0f,0.0f));



	//UPROPERTY 계층구조 만들기
	RootComponent = plate;
	leftSideWall->SetupAttachment(plate);
	rightSideWall->SetupAttachment(plate);
	ceiling->SetupAttachment(plate);
	lampMesh->SetupAttachment(plate);;

	lampLight->SetupAttachment(plate);


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

