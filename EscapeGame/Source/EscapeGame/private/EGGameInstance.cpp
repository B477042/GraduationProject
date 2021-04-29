
// Fill out your copyright notice in the Description page of Project Settings.

#include "EGGameInstance.h"
#include "EGPlayerController.h"
#include "Sound/SoundMix.h"
#include "EGPostProcessVolume.h"
#include "EGPlayerState.h"
#include "EGGameState.h"
#include "AStarFinder.h"

UEGGameInstance::UEGGameInstance()
{
	SaveSlotName = TEXT("TESTSave");
	OptionsSlotName = TEXT("Options");
	UserIndex = 0;
	EGameState = EEGGameState::E_NewGame;

	//static ConstructorHelpers::FClassFinder<USoundMix>Sm_mix(TEXT("SoundMix'/Game/MyFolder/BP_SoundClass/BP_SM_EGSoundMix.BP_SM_EGSoundMix_C'"));
	//if (Sm_mix.Succeeded())
	//{
	//	SM_SoundMixClass = Sm_mix.Class;
	//}
	//static ConstructorHelpers::FClassFinder<USoundClass>

	AStarFinder = nullptr;
	bIsDebugMode = false;
}

//Save Game�� ȣ��� ���� �޴����� �����ϰų� �ڵ����� ������Ʈ�� ����� �� �ϰ��̴�
void UEGGameInstance::SaveGame()
{
	
	auto SaveInstance = NewObject<UEGSaveGame>();
		if (!SaveInstance)return;
	
		
		//������ ���� ����� ��������Ʈ�� ȣ��� �Ѵ�
		//Controller���� ������ ������ �õ��ϰ� �Ѵ�
		//���� ��ϵ� Class : EGPlayerController, ItemActor, EnemyCharacter�� �ڼ�
		OnSaveGamePhaseDelegate.Broadcast(SaveInstance);
		EGLOG(Error, TEXT("Save Game Delegate BroadCasted"));

		//Game State ���� ����
		auto egGameState = Cast<AEGGameState>(GetWorld()->GetGameState());
		if (!egGameState)return;

		//EGameState = EEGGameState::E_LoadGame;
		FString LevelName = GetWorld()->GetMapName();
		LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		SaveInstance->GameProgressData.LevelName = FName(*LevelName);
		

		//���Կ� ����
		UGameplayStatics::SaveGameToSlot(SaveInstance, SaveSlotName,UserIndex);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Save"));
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
	//Load ó���� ������ Player�� BeginPlay�ܰ迡�� ������ �ε带 �õ��Ѵ�
}

void UEGGameInstance::SaveOptions(float sld_Master, float sld_BGM, float sld_SE, float sld_Voice, float sld_UI, FIntPoint ScreenResoultion, EWindowMode::Type WindowMode)
{
	auto SaveInstance = NewObject<UOptionSaveGame>();
	if (!SaveInstance)return;

	SaveInstance->SetValues(sld_Master, sld_BGM, sld_SE, sld_Voice, sld_UI, ScreenResoultion, WindowMode);
	UGameplayStatics::SaveGameToSlot(SaveInstance, OptionsSlotName, UserIndex);
}

UOptionSaveGame* UEGGameInstance::LoadOptions()
{
	//���� ���۽� ����ƴ� �ɼ��� �ҷ��´�.
	//���� �ҷ������� �ִٸ� ���� �÷��̰� ����Ǳ� ������
	//�ɼ��� �ҷ����� �ؼ� �� �ȴ�.


	auto LoadInstance = Cast<UOptionSaveGame>(UGameplayStatics::LoadGameFromSlot(OptionsSlotName, UserIndex));
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("Load Insatnce Failed"));
		return nullptr;
	}



	return LoadInstance;
	

}

const TWeakObjectPtr<AEGPostProcessVolume> UEGGameInstance::GetPostProcessVolume()
{
	return PostProcessVolume;
}
TWeakObjectPtr<class AAStarFinder>UEGGameInstance::GetAStarFinder()
{
	return AStarFinder;
}

bool  UEGGameInstance::SetPostProcessVolume(AEGPostProcessVolume* Object)
{
	if (!Object)return false;

	PostProcessVolume = Object;
	return true;
}
bool  UEGGameInstance::SetAStarFinder(AAStarFinder* Object)
{
	if (!Object)return false;

	if (AStarFinder!=nullptr)
	{
		EGLOG(Error, TEXT("AStarFinder is already Setted"));
		return false;
	}

	AStarFinder = Object;
	return true;


}
