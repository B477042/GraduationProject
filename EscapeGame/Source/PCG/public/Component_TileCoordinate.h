// Fill out your copyright notice in the Description page of Project Settings.
/*
	Ÿ�� ��ǥ�踦 �ٷ�� ������Ʈ
	���� ��ǥ��� Ÿ�� ��ǥ�踦 ��ȯ�ϴ� ������ �Ѵ�
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
	//owner�� Ÿ�� ��ǥ�� ��ġ
	UPROPERTY(VisibleAnywhere, Category = "coord")
		FVector TileCoord;
	//ǥ������ ���� Ÿ�� 1���� ũ��
	UPROPERTY(VisibleAnywhere, Category = "coord")
		FVector TileSize;
};
