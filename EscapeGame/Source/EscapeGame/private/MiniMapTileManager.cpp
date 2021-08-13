// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapTileManager.h"
#include "BaseStruct.h"
//bool AMiniMapTileManager::bIsUniqueObj = false;
// Sets default values
AMiniMapTileManager::AMiniMapTileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Offset_BeginFade = 190.0f;
	Offset_CompeleteFade = 415.0f;

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

		Array_Structures.Add(Casted);

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

void AMiniMapTileManager::SetAllOpacityToZero()
{
	if (Array_Structures.Num() == 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Array is empty"));
		return;
	}

	for (auto it : Array_Structures)
	{
		it->SetTileOpacity(0);
	}
}

void AMiniMapTileManager::CalculateStructsOpacity(const FVector& Pos_Player)
{


	for (auto it : Array_Structures)
	{
		const float DistanceZ = CalcHowFarToPlayer(Pos_Player, it->GetActorLocation());
		
		/*
		* DistanceZ is smaller than Offset CompeleteFade. 
		*
		*/
		if (DistanceZ < Offset_CompeleteFade)
		{
			//Smaller than Offset BeginFade
			if (DistanceZ <= Offset_BeginFade)
			{
				it->SetTileOpacity(1);
			}

			//Calc Percent value
			float Percent = 1 - (DistanceZ - Offset_BeginFade) / (Offset_CompeleteFade - Offset_BeginFade);
			//float LerpValue = FMath::Lerp(Offset_BeginFade, Offset_CompeleteFade, Percent)/Offset_CompeleteFade;

			it->SetTileOpacity(Percent);
		}
		else
		{
			it->SetTileOpacity(0);
		}

	}


	
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
		Thread_CalcOpacity::SetAllOpacityToZero(Manager);
		
		Thread_CalcOpacity::CalcOpacityOfStruct(Manager, Player);
		EGLOG(Warning, TEXT("Thread Off"));

	}

	
}

void Thread_CalcOpacity::SetAllOpacityToZero(AMiniMapTileManager* Manager)
{
	if (!Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("Manager is Nullptr"));
	}
	Manager->SetAllOpacityToZero();

	
}

void Thread_CalcOpacity::CalcOpacityOfStruct( AMiniMapTileManager* Manager, const AActor* Player)
{
	if (!Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("Manager is Nullptr"));
	}
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is Nullptr"));
	}
	
	while (Player->IsValidLowLevel()&& UGameplayStatics::GetGameInstance(Manager))
	{
		/*
			Is Thread Works? 
		*/
		/*UE_LOG(LogTemp, Log, TEXT("Hello Thread"));
		FPlatformProcess::Sleep(0.01);*/

		Manager->CalculateStructsOpacity(Player->GetActorLocation());
		FPlatformProcess::Sleep(0.01);

	}


}
