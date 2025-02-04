// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

//Debug 매크로 선언
DECLARE_LOG_CATEGORY_EXTERN(EGgame, Log, All);

#define EGLOG_CALLINFO (/*FString( __FILE__)+TEXT("->")+*/FString(__FUNCTION__)+TEXT("(")+FString::FromInt(__LINE__)+TEXT(")"))
#define EGLOG_CALLONLY (Verbosity) UE_LOG(EGgame,Verbosity,TEXT("%s"),*EGLOG_CALLINFO)

#define EGLOG(Verbosity,Format, ...) UE_LOG(EGgame,Verbosity,TEXT("%s %s"),*EGLOG_CALLINFO,*FString::Printf (Format, ##__VA_ARGS__))


#define TItem TEXT("Item")
#define TSpawned TEXT("Spawned")
#define TPlayer TEXT("Player")

static FDamageEvent ActorTakeDamageEvent;

static bool DrawingDebugMode=true;
//미니맵 요소들을 랜더링하는 기준 위치. 상대좌표로 이용한다. 30M위에 미니맵용 평면들 출력
const static FVector POS_Minimap= FVector(0,0,3000);

//Set of Six Direction; up,down,forward,backward,left,right
UENUM(BlueprintType)
enum class ESixDirection :uint8
{
	E_Default=0 UMETA(DisplayName = "Default"),
	E_Left UMETA(DisplayName = "Left"),
	E_Right UMETA(DisplayName = "Right"),
	E_Forward UMETA(DisplayName = "Forward"),
	E_Backward UMETA(DisplayName = "Backward"),
	E_Up UMETA(DisplayName = "Up"),
	E_Down UMETA(DisplayName = "Down")

	
};


//#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
//#define ABLOG_S(Verbosity) UE_LOG(ArenaBattle, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
//#define ABLOG(Verbosity, Format, ...) UE_LOG(ArenaBattle, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))