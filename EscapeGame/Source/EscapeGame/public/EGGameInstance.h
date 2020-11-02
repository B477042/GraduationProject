// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"

#include "Engine/GameInstance.h"
#include "EGGameInstance.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadGamePhase);

UCLASS()
class ESCAPEGAME_API UEGGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UEGGameInstance();

	UFUNCTION(BlueprintCallable)
		void SaveGame();
	UFUNCTION(BlueprintCallable)
		void LoadGame();

	FString SaveSlotName;
	int32 UserIndex;

	//Player�� BeginPlay�� ȣ���Ҷ� ����� ��. ��� ���͵��� �ڽ��� ������ �ҷ��´�
	FOnLoadGamePhase OnLoadGamePhaseDelegate;


private:
	
	
};
