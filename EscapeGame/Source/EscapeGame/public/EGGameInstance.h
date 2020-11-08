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

	//Game�� ����. Save file�� ��� ������� �̿��� �� �ִ�.
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		EEGGameState EGameState;


	//Player�� BeginPlay�� ȣ���Ҷ� ����� ��. ��� ���͵��� �ڽ��� ������ �ҷ��´�
	//PostInitiliazeComponents���� �Լ� ���
	FOnLoadGamePhase OnLoadGamePhaseDelegate;

	//Save Game�� ȣ��Ǹ� ����ȴ�
	FOnSaveGamePhase OnSaveGamePhaseDelegate;
 
private:
	
	
};
