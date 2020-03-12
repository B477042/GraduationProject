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
	//PCG의 기준을 원점으로 잡아준다
	SetActorLocation(FVector::ZeroVector);
	SetActorRotation(FRotator::ZeroRotator);

	UE_LOG(LogTemp, Error, TEXT("PCG Generating Start"));
	if(CreatedCount!=0)
		UE_LOG(LogTemp, Error, TEXT("Created Count is not 0!!"));
	/*
	
		타일을 만드는데 필요한 정보
		- 타일을 둘 위치  : Spawn할 때 위치를 정해주면 Tile 내부 코드로 PCG 좌표가 작성된다
							여기서 정해줘야될 것은 World 좌표계에서의 위치가 되버린다.
		- 타일의 크기 : Static 처리로 해결
	*/
	//i를 사용한 이유 : 막히거나 한다면 만들지 않을 것이다
	for (int i = 0; i < TotalTiles; i++)
	{
		////처음 시작하는 것이라면 아직 아무것도 만들지 않았다. .
		//if (CreatedCount == 0)
		//{
		//	
		//	auto g_Tile = generateTile();
		//	tileAtCousor(g_Tile);

		//}
		////주로 이 밑에서 배치가 일어날 예정이다
		//else
		//{

		//}
		auto g_Tile = generateTile();
		tileAtCousor(g_Tile);

	}

	

}

//반환되는 tile은 zero transform을 가진다
AActor* APCGGenerator::generateTile()
{
	CreatedCount++;
	auto CreatedActor = Cast<AActor>(GetWorld()->SpawnActor(ATile::StaticClass()));
	CreatedActor->SetActorRotation(FRotator::ZeroRotator);
	CreatedActor->SetActorLocation(FVector::ZeroVector);
	//완성된 타일을 Tiles에 저장해둔다
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

