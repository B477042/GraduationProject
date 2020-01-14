// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PCG.h"

#include "GameFramework/Actor.h"
#include "TestSpawnActor.h"
#include "PCGConerGenerator.generated.h"

UCLASS()
class PCG_API APCGConerGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APCGConerGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void GenerateConers();
	void GeneratePaths(const AActor& From, const AActor& To);
private:
	FVector generateCoord();
	bool checkRange(const AActor& From,const AActor& To);

private:
	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* Path;
	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* Coner;
	UPROPERTY(EditAnywhere, Category = Location)
		TArray<FVector> ConerCoordinations;

	UPROPERTY(EditAnywhere, Category = Location)
		TArray<TWeakObjectPtr <ATestSpawnActor>> CreatedConers;

	UPROPERTY(EditAnywhere)
		int32 nConer;
	UPROPERTY(EditAnywhere)
		int32 Floor;
	//value : 1 = 1 meter in game. this is a meter value
	UPROPERTY(EditAnywhere)
		int32 XRange;
	
};
/* 
랜덤한 위치에 스폰시켜 본다. 
시켰으면 그 사이에 뭔가 또 스폰 시켜본다

*/