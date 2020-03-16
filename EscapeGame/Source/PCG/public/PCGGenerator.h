// Fill out your copyright notice in the Description page of Project Settings.
/*
	PCG내의 좌표는 PCG의 좌표를 기준으로 한다
	월드에 배치할 때만 월드 좌표계를 따른다

*/
#pragma once

#include "PCG.h"
#include "GameFramework/Actor.h"
#include "PCGGenerator.generated.h"

USTRUCT(BlueprintType, meta = (ToolTip = "PCG 좌표와 월드좌표"))
struct   FCreatingCousor
{
public:
	GENERATED_BODY()

	//CreatingCousor(FVector Location = FVector::ZeroVector, ECreateDirection Direction = ECreateDirection::Forward) :Location(Location), Direction(Direction) {}
		FCreatingCousor()
	{
		Location = FVector::ZeroVector;

	}
	UPROPERTY(VisibleAnywhere,Category= CousorInfor)
	FVector Location;
	UPROPERTY(VisibleAnywhere,Category = CousorInfor)
	ECreateDirection Direction;

};

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
	//방향과 이동량을 묶은 map
	TMap<ECreateDirection, FVector> Map_Dir;
	//타일을 CreateIndex 위치로 옮겨서 맞춰준다.그리고 커서를 진행 방향에 맞게 이동시킨다
	bool tileAtCousor(AActor* Object);

	bool resetCousor(ECreateDirection direction);
	bool isReverseDirection(ECreateDirection Old, ECreateDirection New);
	
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
	//타일의 크기
	UPROPERTY(EditInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		FVector TileSize;
	
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 TotalTiles;

	//타일들의 좌표를 저장한 array
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		TArray<FPCGCoord> coords_tiles;

	////이 좌표에 PCG Tile을 배치할 것이다
	//UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
	//	FVector CreatingCousor;
	//이 좌표에 PCG Tile을 배치할 것이다
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		FCreatingCousor CreatingCousor;

	//지금까지 만들어진 타일들의 총 수 
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 CreatedCount;
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		bool isPCGlunched;
};
