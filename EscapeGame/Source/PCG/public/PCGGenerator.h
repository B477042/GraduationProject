// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PCG.h"
#include "GameFramework/Actor.h"
#include "PCGGenerator.generated.h"

UCLASS()
class PCG_API APCGGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APCGGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RunPCG();
private:
	//Generate One of Tile
	//Save At 'Tiles'
	AActor* generateTile();

private:
	//사용한 타일 타입의 객체들을 담아둔 Array
	UPROPERTY(EditInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> Tiles;
	//한층에 사용하게 될 타일의 갯수
	UPROPERTY(EditInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 n_Tiles;
	//층의 갯수
	UPROPERTY(EditInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 Floors;
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 TotalTiles;
	//타일들의 좌표를 저장한 array
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		TArray<FVector> coords_tiles;

};
