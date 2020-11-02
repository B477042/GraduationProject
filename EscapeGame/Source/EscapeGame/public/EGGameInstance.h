// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EGSaveGame.h"
#include "Engine/GameInstance.h"
#include "EGGameInstance.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadGamePhase, const UEGSaveGame*, LoadInstance );

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

	//Player가 BeginPlay를 호출할때 실행될 것. 모든 엑터들은 자신의 정보를 불러온다
	//PostInitiliazeComponents에서 함수 등록
	FOnLoadGamePhase OnLoadGamePhaseDelegate;


private:
	
	
};
