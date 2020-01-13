// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PCG.h"

#include "GameFramework/Actor.h"
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
	void GeneratePaths(const FVector& From, const FVector& To);
private:
	FVector generateCoord();
	bool checkRange(const FVector& From,const FVector& To);

private:
	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* Path;
	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* Coner;
	UPROPERTY(EditAnywhere, Category = Location)
		TArray<FVector> ConerCoordinations;
	UPROPERTY(EditAnywhere)
		int32 nConer;
	UPROPERTY(EditAnywhere)
		int32 Floor;
	UPROPERTY(EditAnywhere)
		int32 XRange;
	
};
/* 
������ ��ġ�� �������� ����. 
�������� �� ���̿� ���� �� ���� ���Ѻ���

*/