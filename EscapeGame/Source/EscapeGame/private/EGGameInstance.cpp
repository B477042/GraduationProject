
// Fill out your copyright notice in the Description page of Project Settings.

#include "EGGameInstance.h"
#include "EGPlayerController.h"

#include "EGPlayerState.h"
#include "EGGameState.h"

UEGGameInstance::UEGGameInstance()
{
	SaveSlotName = TEXT("TESTSave");
	UserIndex = 0;
	EGameState = EEGGameState::E_NewGame;
}

//Save Game이 호출될 경우는 메뉴에서 저장하거나 자동저장 오브젝트와 닿았을 때 일것이다
void UEGGameInstance::SaveGame()
{
	
	auto SaveInstance = NewObject<UEGSaveGame>();
		if (!SaveInstance)return;
	
		

		//Player 정보 저장
		auto playerCon = Cast<AEGPlayerController>(GetWorld()->GetFirstPlayerController());
		if (!playerCon)return;
	
		playerCon->SaveGame(SaveInstance);
	
		//Enemy 정보 저장
	
	
		//Item 정보 저장
	
	
		//Game State 정보 저장
		auto egGameState = Cast<AEGGameState>(GetWorld()->GetGameState());
		if (!egGameState)return;

		//EGameState = EEGGameState::E_LoadGame;
		FString LevelName = GetWorld()->GetMapName();
		LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		SaveInstance->GameProgressData.LevelName = FName(*LevelName);
		

		//슬롯에 저장
		UGameplayStatics::SaveGameToSlot(SaveInstance, SaveSlotName,UserIndex);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Save"));
		EGLOG(Error, TEXT("Load Set Move To : %s"), *SaveInstance->GameProgressData.LevelName.ToString());
}

void UEGGameInstance::LoadGame()
{
	//레벨을 오픈하고 게임의 진행 상황을 LoadGame으로 바꿔준다.
	//각 Controller와 오브젝트는 게임이 시작될 때 Load 게임인 상태인지 확인하고
	//Load Game이라면 정보를 불러온다
	
	/*
		Player의 BeginPlay에 맞춰 정보들을 로딩하기로 한다.
	
	*/

	//LoadGame 상태로
	EGameState = EEGGameState::E_LoadGame;
	

	auto LoadInstance = Cast<UEGSaveGame> (UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("Load Insatnce Failed"));
		return; 
	}



	EGLOG(Error, TEXT("Load Set Move To : %s"), *LoadInstance->GameProgressData.LevelName.ToString());
	UGameplayStatics::OpenLevel(this,LoadInstance->GameProgressData.LevelName);
	EGLOG(Error, TEXT("Load Complete"));
}

