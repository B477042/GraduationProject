// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapTileManager.h"
#include "BaseStruct.h"
bool AMiniMapTileManager::bIsUniqueObj = false;
// Sets default values
AMiniMapTileManager::AMiniMapTileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMiniMapTileManager::BeginPlay()
{
	Super::BeginPlay();
	EGLOG(Warning, TEXT("Manager Begin"));
	/*
	*	If There is any other Object that equal type exist
	*	Destroy this Object
	*/
	if (!bIsUniqueObj)
	{
		bIsUniqueObj = true;
	}
	else
	{
		Destroy();
	}
	//Collect All 'ABaseStruct' based objects
	auto World = GetWorld();
	if (!World)
	{
		return;
	}
	TArray<AActor*>Results;

	UGameplayStatics::GetAllActorsOfClass(World, ABaseStruct::StaticClass(), Results);

	if (Results.Num() == 0)
	{
		EGLOG(Warning, TEXT("There isn't any struct"));
		return;
	}

	/*
	*  OBJ Cast
	*	AActor ===========> ABaseStruct
	*/
	for (auto it : Results)
	{
		ABaseStruct* Casted = Cast<ABaseStruct>(it);
		if (!Casted)
		{
			EGLOG(Error, TEXT("Casting Failed"));
			return;
		}

		Array_Structs.Add(Casted);

	}



}

void AMiniMapTileManager::BeginDestroy()
{
	Super::BeginDestroy();
	EGLOG(Warning, TEXT("Manager Destroy"));
}

// Called every frame
void AMiniMapTileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

