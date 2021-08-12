// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapTileManager.h"
#include "BaseStruct.h"
//bool AMiniMapTileManager::bIsUniqueObj = false;
// Sets default values
AMiniMapTileManager::AMiniMapTileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Offset_BeginFade = 100.0f;
	Offset_CompeleteFade = 150.0f;

}

// Called when the game starts or when spawned
void AMiniMapTileManager::BeginPlay()
{
	Super::BeginPlay();
	EGLOG(Warning, TEXT("Manager Begin"));
	///*
	//*	If There is any other Object that equal type exist
	//*	Destroy this Object
	//*/
	//if (!bIsUniqueObj)
	//{
	//	bIsUniqueObj = true;
	//}
	//else
	//{
	//	EGLOG(Error, TEXT("Is Not Unique Manager"));
	//	Destroy();
	//}
	


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
	EGLOG(Warning, TEXT("Task Start"));

	
}

void AMiniMapTileManager::BeginDestroy()
{
	Super::BeginDestroy();
	EGLOG(Warning, TEXT("Manager Destroy"));
}

float AMiniMapTileManager::CalcHowFarToPlayer(const FVector& Pos_Player, const FVector& Pos_Path)
{
	float Result = 0.0f;

	Result = FMath::Abs(Pos_Player.Z - Pos_Path.Z);

	return Result;
}




// Called every frame
void AMiniMapTileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}






//==========================================================================================================
//Thread


void CalcMiniMapTileAsyncTask::DoWork()
{
	

	//Task Parameter Check 
	if (Manager && Player)
	{
		/*
		* ===============================================
		*		How To Work
		* 
		*	Goal : Calculate Opacity of all of 'MiniMap tile'
		*	
		*	Solution
		* 
			1) As Default, Set Tiles's Opacity to 0
			2) In While Loop, Calaculate Z Distance Between Tiles and Player
			3) 
		* ================================================ 
		*/


		EGLOG(Warning, TEXT("Thread On"));

		//#1 Set Opacity to 0

		
		Thread_CalcOpacity::CalcOpacityOfStruct(Manager, Player);
		EGLOG(Warning, TEXT("Thread Off"));

	}

	
}

void Thread_CalcOpacity::SetAllOpacityToZero(const AMiniMapTileManager* Manager)
{
}

void Thread_CalcOpacity::CalcOpacityOfStruct(const AMiniMapTileManager* Manager, const AActor* Player)
{
	//int num = 0;
	//EGLOG(Error, TEXT("Thread : %s"), *Manager->GetName());
	//for (int i = 0; i < 1000000000; i++)
	//{
	//	num += i;

	//}
	//UE_LOG(LogTemp, Warning, TEXT("Thread : %d"), num);



}
