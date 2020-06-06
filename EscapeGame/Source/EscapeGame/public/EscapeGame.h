// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Kismet/GameplayStatics.h"

//Debug 매크로 선언
DECLARE_LOG_CATEGORY_EXTERN(EGgame, Log, All);

#define EGLOG_CALLINFO (/*FString( __FILE__)+TEXT("->")+*/FString(__FUNCTION__)+TEXT("(")+FString::FromInt(__LINE__)+TEXT(")"))
#define EGLOG_CALLONLY (Verbosity) UE_LOG(EGgame,Verbosity,TEXT("%s"),*EGLOG_CALLINFO)

#define EGLOG(Verbosity,Format, ...) UE_LOG(EGgame,Verbosity,TEXT("%s %s"),*EGLOG_CALLINFO,*FString::Printf (Format, ##__VA_ARGS__))

static FDamageEvent ActorTakeDamageEvent;

static bool DrawingDebugMode=true;


//#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
//#define ABLOG_S(Verbosity) UE_LOG(ArenaBattle, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
//#define ABLOG(Verbosity, Format, ...) UE_LOG(ArenaBattle, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))