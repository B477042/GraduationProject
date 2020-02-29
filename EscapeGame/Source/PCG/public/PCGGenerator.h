// Fill out your copyright notice in the Description page of Project Settings.
/*
	PCG���� ��ǥ�� PCG�� ��ǥ�� �������� �Ѵ�
	���忡 ��ġ�� ���� ���� ��ǥ�踦 ������

*/
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
	//����� �̵����� ���� map
	TMap<ECreateDirection, FVector> Map_Dir;

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
		int32 TailSize;
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 TotalTiles;
	//Ÿ�ϵ��� ��ǥ�� ������ array
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		TArray<FPCGCoord> coords_tiles;
	//���ݱ��� ������� Ÿ�ϵ��� �� �� 
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		int32 CreatedCount;
	UPROPERTY(VisibleInstanceOnly, Category = "PCGSystem", meta = (AllowPrivateAccess = "true"))
		bool isPCGlunched;
};
