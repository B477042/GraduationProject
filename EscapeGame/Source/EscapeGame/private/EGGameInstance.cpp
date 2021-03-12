
// Fill out your copyright notice in the Description page of Project Settings.

#include "EGGameInstance.h"
#include "EGPlayerController.h"
#include "Sound/SoundMix.h"
#include "EGPostProcessVolume.h"
#include "EGPlayerState.h"
#include "EGGameState.h"

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

	
	bIsDebugMode = false;
}

//Save Game이 호출될 경우는 메뉴에서 저장하거나 자동저장 오브젝트와 닿았을 때 일것이다
void UEGGameInstance::SaveGame()
{
	
	auto SaveInstance = NewObject<UEGSaveGame>();
		if (!SaveInstance)return;
	
		
		//정보의 저장 방식은 델리게이트의 호출로 한다
		//Controller에서 정보의 저장을 시도하게 한다
		//현재 등록된 Class : EGPlayerController, ItemActor, EnemyCharacter의 자손
		OnSaveGamePhaseDelegate.Broadcast(SaveInstance);
		EGLOG(Error, TEXT("Save Game Delegate BroadCasted"));

		//Game State 정보 저장
		auto egGameState = Cast<AEGGameState>(GetWorld()->GetGameState());
		if (!egGameState)return;

		//EGameState = EEGGameState::E_LoadGame;
		FString LevelName = GetWorld()->GetMapName();
		LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		SaveInstance->GameProgressData.LevelName = FName(*LevelName);
		

		//슬롯에 저장
		UGameplayStatics::SaveGameToSlot(SaveInstance, SaveSlotName,UserIndex);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Save"));
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
	//Load 처리가 끝나면 Player가 BeginPlay단계에서 데이터 로드를 시도한다
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
	//게임 시작시 저장됐던 옵션을 불러온다.
	//만약 불러온적이 있다면 게임 플레이가 종료되기 전까지
	//옵션을 불러오게 해선 안 된다.


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

bool  UEGGameInstance::SetPostProcessVolume(AEGPostProcessVolume* Object)
{
	if (!Object)return false;

	PostProcessVolume = Object;
	return true;
}

