// Fill out your copyright notice in the Description page of Project Settings.
/*
	PCG���� ��ǥ�� PCG�� ��ǥ�� �������� �Ѵ�
	���忡 ��ġ�� ���� ���� ��ǥ�踦 ������

*/
#pragma once

#include "PCG.h"
#include "GameFramework/Actor.h"
#include "PCGGenerator.generated.h"

USTRUCT(BlueprintType, meta = (ToolTip = "PCG ��ǥ�� ������ǥ"))
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
	//����� �̵����� ���� map
	TMap<ECreateDirection, FVector> Map_Dir;
	//Ÿ���� CreateIndex ��ġ�� �Űܼ� �����ش�.�׸��� Ŀ���� ���� ���⿡ �°� �̵���Ų��
	bool tileAtCousor(AActor* Object);

	bool resetCousor(ECreateDirection direction);
	bool isReverseDirection(ECreateDirection Old, ECreateDirection New);
	
private:
	//����� Ÿ�� Ÿ���� ��ü���� ��Ƶ� Array
	UPROPERTY(EditInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> Tiles;
	//������ ����ϰ� �� Ÿ���� ����
	UPROPERTY(EditInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 n_Tiles;
	//���� ����
	UPROPERTY(EditInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 Floors;
	//Ÿ���� ũ��
	UPROPERTY(EditInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		FVector TileSize;
	
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 TotalTiles;

	//Ÿ�ϵ��� ��ǥ�� ������ array
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		TArray<FPCGCoord> coords_tiles;

	////�� ��ǥ�� PCG Tile�� ��ġ�� ���̴�
	//UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
	//	FVector CreatingCousor;
	//�� ��ǥ�� PCG Tile�� ��ġ�� ���̴�
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		FCreatingCousor CreatingCousor;

	//���ݱ��� ������� Ÿ�ϵ��� �� �� 
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 CreatedCount;
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		bool isPCGlunched;
};
