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

		//Tail의 반지름은 BoxExtent의 입력값인 반지름의 수치와 같다. 그래서 2배로 늘려야
		//간격으로 사용 가능한 값이 나온다. 이 값으로 PCG 좌표를 정한다
		PCGCoord = WorldCoord / (TailRadius*2);

	}

private:

	FVector PCGCoord;
	FVector WorldCoord;
	FVector TailRadius;
};

