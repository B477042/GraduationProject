
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

//Save Game�� ȣ��� ���� �޴����� �����ϰų� �ڵ����� ������Ʈ�� ����� �� �ϰ��̴�
void UEGGameInstance::SaveGame()
{
	
	auto SaveInstance = NewObject<UEGSaveGame>();
		if (!SaveInstance)return;
	
		

		//Player ���� ����
		auto playerCon = Cast<AEGPlayerController>(GetWorld()->GetFirstPlayerController());
		if (!playerCon)return;
	
		playerCon->SaveGame(SaveInstance);
	
		//Enemy ���� ����
	
	
		//Item ���� ����
	
	
		//Game State ���� ����
		auto egGameState = Cast<AEGGameState>(GetWorld()->GetGameState());
		if (!egGameState)return;

		//EGameState = EEGGameState::E_LoadGame;
		FString LevelName = GetWorld()->GetMapName();
		LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		SaveInstance->GameProgressData.LevelName = FName(*LevelName);
		

		//���Կ� ����
		UGameplayStatics::SaveGameToSlot(SaveInstance, SaveSlotName,UserIndex);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Save"));
		EGLOG(Error, TEXT("Load Set Move To : %s"), *SaveInstance->GameProgressData.LevelName.ToString());
}

void UEGGameInstance::LoadGame()
{
	//������ �����ϰ� ������ ���� ��Ȳ�� LoadGame���� �ٲ��ش�.
	//�� Controller�� ������Ʈ�� ������ ���۵� �� Load ������ �������� Ȯ���ϰ�
	//Load Game�̶�� ������ �ҷ��´�
	
	/*
		Player�� BeginPlay�� ���� �������� �ε��ϱ�� �Ѵ�.
	
	*/

	//LoadGame ���·�
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

