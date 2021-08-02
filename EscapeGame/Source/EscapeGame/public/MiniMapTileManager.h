// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "MiniMapTileManager.generated.h"

/*
*	To Control Opacity of the UTileMeshComponent's Matreial Instances
*	Calculate Distance of Z Axis Between Character and Path Objects
*	Then, Lerp Calculated Value and Offest Abs. 
*	
*	A New Thread [ ] take care of this all calculate works. 
* 
*	Object : 
*	Use UE4 Multi-Thread to Understand How UE4's Multi-Thread Works
*	in Game. 
*/


UCLASS()
class ESCAPEGAME_API AMiniMapTileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMiniMapTileManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy()override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "MultiThread")
		TArray<class ABaseStruct*> Array_Structs;
	
	//If True it means There is other object of this type. 
	static bool bIsUniqueObj;

};

namespace Thread_CalcOpacity
{
	static void CalcOpacityOfStruct(const AMiniMapTileManager* Manager,	const AActor* Player)
	{
		int num = 0;
		EGLOG(Error, TEXT("Thread : %s"), *Manager->GetName());
		for (int i = 0; i < 100000; i++)
		{
			num += i;
		
		}
		UE_LOG(LogTemp, Log, TEXT("Thread : %d"),num);
	}
}

/*
*	Reference Tutorial : https://www.orfeasel.com/implementing-multithreading-in-ue4/
*	AsyncTask Type Calss. 
* 
*/
class CalcMiniMapTileAsyncTask :public FNonAbandonableTask
{
	const AMiniMapTileManager* Manager;
	const AActor* Player;

public:
	CalcMiniMapTileAsyncTask(const AMiniMapTileManager* Manager, const AActor* Player)
	{
		this->Manager = Manager;
		this->Player = Player;
	}


	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(PrimeCalculationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	void DoWork()
	{
		

		if (Manager && Player)
		{
			EGLOG(Warning, TEXT("Thread On"));
			Thread_CalcOpacity::CalcOpacityOfStruct(Manager, Player);
		}

	}

};