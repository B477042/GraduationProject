// Fill out your copyright notice in the Description page of Project Settings.

#include "PathfindTest.h"
#include "Logging.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FPathfindTest"

void FPathfindTest::StartupModule()
{
}

void FPathfindTest::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPathfindTest, PathfindTest);