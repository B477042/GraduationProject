// Fill out your copyright notice in the Description page of Project Settings.


#include "PCGGenerator.h"

// Sets default values
APCGGenerator::APCGGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	n_Tiles = 10;
	Floors = 1;
	TailSize = 50;
	TotalTiles = n_Tiles * Floors;
	CreatedCount=0;
	isPCGlunched = false;

	Map_Dir.Add(ECreateDirection::Forward,FVector(1.0f,0.0f,0.0f));
	Map_Dir.Add(ECreateDirection::Backward, FVector(0.0f, 1.0f, 0.0f));
	Map_Dir.Add(ECreateDirection::Left, FVector(0.0f, 1.0f, 0.0f));
	Map_Dir.Add(ECreateDirection::Right, FVector(0.0f, -1.0f, 0.0f));
}

// Called when the game starts or when spawned
void APCGGenerator::BeginPlay()
{
	Super::BeginPlay();
	TotalTiles = n_Tiles * Floors;
	RunPCG();
}

// Called every frame
void APCGGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APCGGenerator::RunPCG()
{
	if (isPCGlunched == true)return;

	isPCGlunched = true;
	//PCG�� ������ �������� ����ش�
	SetActorLocation(FVector::ZeroVector);
	SetActorRotation(FRotator::ZeroRotator);

	//i�� ����� ���� : �����ų� �Ѵٸ� ������ ���� ���̴�
	for (int i = 0; i < TotalTiles; i++)
		
	{
		//ó�� �����ϴ� ���̶�� ���� �ƹ��͵� ������ �ʾҴ�. .
		if (CreatedCount == 0)
		{
			
		}
		

	}

}

AActor* APCGGenerator::generateTile()
{
	CreatedCount++;


	return nullptr;
}

