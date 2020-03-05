// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include"PCG.generated.h"

//���� PCG �����ڰ� ���� ����� ���� ����. �⺻�� Forward
UENUM(BlueprintType)
enum class ECreateDirection : uint8
{
	Forward = 0, Backward, Left, Right
};

USTRUCT(BlueprintType, meta = (ToolTip = "PCG ��ǥ�� ������ǥ"))
struct FPCGCoord
{
public:
	GENERATED_BODY()
//Caution!! Set Radius MUST!!!!
	FPCGCoord()
	{
		
	}
	//Input PCG Coord
	
	const FVector GetPCGCoord()
	{
		return PCGCoord;
	}
	const FVector GetWorldCoord()
	{
		return WorldCoord;
	}
	void SetDefaultValue(FVector WorldCoord, FVector TailRadius = FVector::ZeroVector)
	{
		this->TailRadius = TailRadius;
		this->WorldCoord = WorldCoord;

		//Tail�� �������� BoxExtent�� �Է°��� �������� ��ġ�� ����. �׷��� 2��� �÷���
		//�������� ��� ������ ���� ���´�. �� ������ PCG ��ǥ�� ���Ѵ�
		PCGCoord = WorldCoord / (TailRadius*2);

	}

private:

	FVector PCGCoord;
	FVector WorldCoord;
	FVector TailRadius;
};

