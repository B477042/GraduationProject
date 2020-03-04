// Fill out your copyright notice in the Description page of Project Settings.

/*
	PCG에 사용할 기본적인 타일. 
	이 타일을 기본으로 통로와 계단이 만들어진다
	이 타일은 사이즈만 정의한다.

	테스트 용으로 Mesh를 붙여준다

*/




#pragma once

#include "PCG.h"
#include "GameFramework/Actor.h"
#include "Component_TileCoordinate.h"
#include "Tile.generated.h"

UCLASS()
class PCG_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector GetTailRadius();
	
private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Mesh;
	//타일의 전체 크기로서 측정하는데 사용하게 될 것
	UPROPERTY(EditAnywhere, Category = "Box", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* BoxCollision;
	//Box의 반지름. BoxCollision은 반지름을 이용한다
	FVector TailRadius;

	FPCGCoord PCGCoord;
	
	//UPROPERTY(VisibleAnywhere, Category = "TileCoord")
	//	UComponent_TileCoordinate* TileSystem;

};
