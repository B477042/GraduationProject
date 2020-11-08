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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGamePhase, UEGSaveGame*, SaveInstance);

UENUM(BlueprintType)
enum class EEGGameState :uint8
{
	E_InPlay = 0 UMETA(DisplayName = "InPlay"),
	E_NewGame  UMETA(DisplayName = "NewGame"),
	E_LoadGame UMETA(DisplayName = "LoadGame"),
	E_ClearGame UMETA(DisplayName = "ClearGame"),
	E_NextStage UMETA(DisplayName = "NextStage")

};

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

	//Game의 상태. Save file을 어떻게 사용할지 이용할 수 있다.
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		EEGGameState EGameState;


	//Player가 BeginPlay를 호출할때 실행될 것. 모든 엑터들은 자신의 정보를 불러온다
	//PostInitiliazeComponents에서 함수 등록
	FOnLoadGamePhase OnLoadGamePhaseDelegate;

	//Save Game이 호출되면 실행된다
	FOnSaveGamePhase OnSaveGamePhaseDelegate;
 
private:
	
	
};
