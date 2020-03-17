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
	Map_Dir.Add(ECreateDirection::Backward, FVector(-1.0f, 0.0f, 0.0f)*TileSize);
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

	//배치를 랜덤하게 할 것이다
	/*	
		3~5칸을 진행한 후방향을 바꿔서 또 3~5칸을 진행하게 될 것이다.
		randRange로 몇 칸을 진행하게 될지 정하고
		randCount로 횟수를 센다

		randCount가 Range와 같거나 커지면
		새로 Rnage를 정하고 Count를 초기화시킨다

		
	*/
	int randRange = FMath::RandRange(3, 5);
	int randCount = 0;

	for (int i = 0; i < TotalTiles; i++)
	{
		
		//tile을 만든 후, tile을 커서 위치로 옮겨준다
		auto g_Tile = generateTile();
		tileAtCousor(g_Tile);

		//만든 후 rand 변수들을 조정한다
		randCount++;
		UE_LOG(LogTemp, Warning, TEXT("Current direct : %d"), CreatingCousor.Direction);
		//rand range 수만큼 만들었을 경우		
		if (randCount >= randRange)
		{
			randCount = 0;
			randRange = FMath::RandRange(3, 5);
			ECreateDirection temp_direction = CreatingCousor.Direction;

			
			CreatingCousor.Direction =ECreateDirection ( FMath::RandRange(0,3));
			
			
		
			////방향을 랜덤하게 조정을 해줄 것인데, 서로 상반되지 않게 해줘야 된다. 
			while (isReverseDirection(temp_direction, CreatingCousor.Direction))
			{
				CreatingCousor.Direction = ECreateDirection(FMath::RandRange(0, 3));
			}
			
			UE_LOG(LogTemp, Warning, TEXT("Next direct : %d"), CreatingCousor.Direction);
		}
		

	}
	/*
		2020 03 17  
			: 랜덤하게 4방향하게 잘 뻗어 나간다
		문제점
		1. 저대로 놨두면 교차가 생긴다. 교차가 됐을 때 이벤트를 호출해서 
		교차로 처리를 하는게 나아보인다.

		Tile에 겹치는 이벤트를 넣어준다.

	*/

	

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
/*
	커서를 처음 지점으로 되돌리고 방향도 전환시킨다
 */
bool APCGGenerator::resetCousor(ECreateDirection direction)
{
	CreatingCousor.Location = FVector::ZeroVector;
	CreatingCousor.Direction = direction;
	return true;
}
/*
		isReverseDirection(ECreateDirection Old, ECreateDirection New)
		Old는 새로 배정되기 전의 방향이고
		new는 새로 배정된 방향이 들어와야 된다

		둘이 서로 상반되게 -><- 된다면

		생성방향이 역순으로 되버려 같은 구간에 똑같은게 또 생성된다

		반약 서로 상반되면 ture를 리턴한다

		상반되지 않다면 false
	*/
bool APCGGenerator::isReverseDirection(ECreateDirection Old, ECreateDirection New)
{

	
	if (Old == ECreateDirection::Forward &&New == ECreateDirection::Backward)
		return true;
	else if (Old == ECreateDirection::Backward &&New == ECreateDirection::Forward)
		return true;
	else if (Old == ECreateDirection::Left &&New == ECreateDirection::Right)
		return true;
	else if (Old == ECreateDirection::Right &&New == ECreateDirection::Left)
		return true;
	else
		return false;
}

