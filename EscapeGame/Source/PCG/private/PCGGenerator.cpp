// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGGenerator.h"
#include "Tile.h"

// Sets default values
APCGGenerator::APCGGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	n_Tiles = 10;
	Floors = 1;
	//TailSize = 50;
	TotalTiles = n_Tiles * Floors;
	CreatedCount=0;
	isPCGlunched = false;
	

	
}

// Called when the game starts or when spawned
void APCGGenerator::BeginPlay()
{
	Super::BeginPlay();
	TotalTiles = n_Tiles * Floors;
	TileSize = ATile::GetTileRadius() * 2.0f;
	Map_Dir.Add(ECreateDirection::Forward, FVector(1.0f, 0.0f, 0.0f)*TileSize);
	Map_Dir.Add(ECreateDirection::Backward, FVector(0.0f, 1.0f, 0.0f)*TileSize);
	Map_Dir.Add(ECreateDirection::Left, FVector(0.0f, 1.0f, 0.0f)*TileSize);
	Map_Dir.Add(ECreateDirection::Right, FVector(0.0f, -1.0f, 0.0f)*TileSize);

	RunPCG();
}

// Called every frame
void APCGGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APCGGenerator::RunPCG()
{
	if (isPCGlunched == true)
	{
		UE_LOG(LogTemp, Error, TEXT("PCG has been lunched"));
		return;
	}

	if (GetWorld() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("World is nullptr"));
		return;
	}
	isPCGlunched = true;
	//PCG�� ������ �������� ����ش�
	SetActorLocation(FVector::ZeroVector);
	SetActorRotation(FRotator::ZeroRotator);

	UE_LOG(LogTemp, Error, TEXT("PCG Generating Start"));
	if(CreatedCount!=0)
		UE_LOG(LogTemp, Error, TEXT("Created Count is not 0!!"));
	/*
	
		Ÿ���� ����µ� �ʿ��� ����
		- Ÿ���� �� ��ġ  : Spawn�� �� ��ġ�� �����ָ� Tile ���� �ڵ�� PCG ��ǥ�� �ۼ��ȴ�
							���⼭ ������ߵ� ���� World ��ǥ�迡���� ��ġ�� �ǹ�����.
		- Ÿ���� ũ�� : Static ó���� �ذ�
	*/
	//i�� ����� ���� : �����ų� �Ѵٸ� ������ ���� ���̴�
	for (int i = 0; i < TotalTiles; i++)
	{
		////ó�� �����ϴ� ���̶�� ���� �ƹ��͵� ������ �ʾҴ�. .
		//if (CreatedCount == 0)
		//{
		//	
		//	auto g_Tile = generateTile();
		//	tileAtCousor(g_Tile);

		//}
		////�ַ� �� �ؿ��� ��ġ�� �Ͼ �����̴�
		//else
		//{

		//}
		auto g_Tile = generateTile();
		tileAtCousor(g_Tile);

	}

	

}

//��ȯ�Ǵ� tile�� zero transform�� ������
AActor* APCGGenerator::generateTile()
{
	CreatedCount++;
	auto CreatedActor = Cast<AActor>(GetWorld()->SpawnActor(ATile::StaticClass()));
	CreatedActor->SetActorRotation(FRotator::ZeroRotator);
	CreatedActor->SetActorLocation(FVector::ZeroVector);
	//�ϼ��� Ÿ���� Tiles�� �����صд�
	Tiles.Add(CreatedActor);

	return CreatedActor;
}

bool APCGGenerator::tileAtCousor(AActor* Object)
{
	/*if (CreatingCousor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("creatingCousor is nullptr"));
		return false;
	}*/
	
	Object->SetActorLocation(CreatingCousor.Location);

	if (!Map_Dir.Contains(CreatingCousor.Direction))
	{
		UE_LOG(LogTemp, Warning, TEXT("Map_Dir has not contain that Direction"));
		return false;
	}

	CreatingCousor.Location += Map_Dir[CreatingCousor.Direction];
	

	return true;
}

