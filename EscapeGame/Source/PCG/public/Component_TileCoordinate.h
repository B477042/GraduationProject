// Fill out your copyright notice in the Description page of Project Settings.
/*
	타일 좌표계를 다루는 컴포넌트
	월드 좌표계와 타일 좌표계를 변환하는 역할을 한다
*/


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_TileCoordinate.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PCG_API UComponent_TileCoordinate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_TileCoordinate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void LoadTileSize(const FVector& Other);
	//Return Tile Coord
	const FVector GetTileCoord();
	//Retrun Inputed FVector To Tile Coord
	 FVector ConvertWorldToTile( FVector Other);
	const FVector ConvertTileToWorld();
	
private:
	//owner의 타일 좌표계 위치
	UPROPERTY(VisibleAnywhere, Category = "coord")
		FVector TileCoord;
	//표준으로 사용될 타일 1개의 크기
	UPROPERTY(VisibleAnywhere, Category = "coord")
		FVector TileSize;
};
