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

	FPCGCoord()
	{

	}
	//Input PCG Coord
	void SetCoord(FVector Input, int TailSize)
	{
		PCGCoord = Input;
		WorldCoord = Input * TailSize;
	}
	const FVector GetPCGCoord()
	{
		return PCGCoord;
	}
	const FVector GetWorldCoord()
	{
		return WorldCoord;
	}

private:

	FVector PCGCoord;
	FVector WorldCoord;
};

