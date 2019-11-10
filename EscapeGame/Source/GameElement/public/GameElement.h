// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

//Debug 매크로 선언
DECLARE_LOG_CATEGORY_EXTERN(EGgame, Log, All);

#define EGLOG_CALLINFO (/*FString( __FILE__)+TEXT("->")+*/FString(__FUNCTION__)+TEXT("(")+FString::FromInt(__LINE__)+TEXT(")"))
#define EGLOG_S(Verbosity) UE_LOG(EGgame,Verbosity,TEXT("%s"),*EGLOG_CALLINFO)

#define EGLOG(Verbosity,Format, ...) UE_LOG(EGgame,Verbosity,TEXT("%s %s"),*EGLOG_CALLINFO,*FString::Printf (Format, ##__VA_ARGS__))