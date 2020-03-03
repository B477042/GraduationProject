// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include"PCG.generated.h"

//현재 PCG 생성자가 블럭을 만드는 진행 방향. 기본은 Forward
UENUM(BlueprintType)
enum class ECreateDirection : uint8
{
	Forward = 0, Backward, Left, Right
};

USTRUCT(BlueprintType, meta = (ToolTip = "PCG 좌표와 월드좌표"))
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

