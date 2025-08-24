
// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealCore/EGGameInstance.h"



#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"
#include "UnrealCore/EGGameState.h"
#include "UnrealCore/SaveGame/EGSaveGame.h"
#include "UnrealCore/SaveGame/OptionSaveGame.h"
#include "Modules/ModuleManager.h"
#include "AbilitySystemGlobals.h"


UEGGameInstance::UEGGameInstance()
{
 
	UserIndex = 0;
	EGameState = EEGGameState::E_NewGame;


	static ConstructorHelpers::FClassFinder<UUserWidget>UI_LOADING(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_LoadingScreen.UI_LoadingScreen_C'"));
	if (UI_LOADING.Succeeded())
	{
		LoadingScreenWidgetClass = UI_LOADING.Class;
	}
	
		

	AStarFinder = nullptr;
	bIsDebugMode = false;
}
void UEGGameInstance::Init()
{
	Super::Init();

	if (!UI_LoadingScreeen)
		UI_LoadingScreeen = CreateWidget<UUserWidget>(this, LoadingScreenWidgetClass);
	if (!UI_LoadingScreeen)
	{
		EGLOG(Error, TEXT("Can't Create Loading Screen"));
		return;
	}

	//Check Save Data File
	USaveGame* checkSaveData= UGameplayStatics::LoadGameFromSlot(Name_SaveSlot0, UserIndex);
	if (!checkSaveData)
	{
		auto SaveInstance = NewObject<UEGSaveGame>();
		if (!SaveInstance)return;
		UGameplayStatics::SaveGameToSlot(SaveInstance, Name_SaveSlot0, UserIndex);
		EGLOG(Error, TEXT("Can't find Save Data. Create New One"));
	}

	USaveGame* checkOptionsData = UGameplayStatics::LoadGameFromSlot(Name_OptionsSlot, UserIndex);
	if (!checkOptionsData)
	{
		auto OptionsInstance = NewObject<UOptionSaveGame>();
		if (!OptionsInstance)return;
		UGameplayStatics::SaveGameToSlot(OptionsInstance, Name_OptionsSlot, UserIndex);
		EGLOG(Error, TEXT("Can't find Options Data. Create New One"));
	}
	USaveGame* checkCPData = UGameplayStatics::LoadGameFromSlot(Name_CheckPointSlot, UserIndex);
	if (!checkCPData)
	{
		auto SaveInstance = NewObject<UEGSaveGame>();
		if (!SaveInstance)return;
		UGameplayStatics::SaveGameToSlot(SaveInstance, Name_CheckPointSlot, UserIndex);
		EGLOG(Error, TEXT("Can't find Check Point Data. Create New One"));
	}




	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UEGGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UEGGameInstance::EndLoadingScreen);

	// Gas init
	UAbilitySystemGlobals& gameAbilityGlobal = UAbilitySystemGlobals::Get();
	if (!gameAbilityGlobal.IsAbilitySystemGlobalsInitialized())
	{
		gameAbilityGlobal.InitGlobalData();
		gameAbilityGlobal.InitGlobalTags();
	}
}


//Save Game�� ȣ��� ���� �޴����� �����ϰų� �ڵ����� ������Ʈ�� ����� �� �ϰ��̴�
void UEGGameInstance::SaveGame(const EEGSaveSlot SaveSlot)
{
	
	auto SaveInstance = NewObject<UEGSaveGame>();
		if (!SaveInstance)return;
	
		
		//������ ���� ����� ��������Ʈ�� ȣ��� �Ѵ�
		//Controller���� ������ ������ �õ��ϰ� �Ѵ�
		//���� ��ϵ� Class : EGPlayerController, ItemActor, EnemyCharacter�� �ڼ�
		OnSaveGamePhaseDelegate.Broadcast(SaveInstance);
		EGLOG(Error, TEXT("Save Game Delegate BroadCasted"));

		//Save Game State Informations
		auto egGameState = Cast<AEGGameState>(GetWorld()->GetGameState());
		if (!egGameState)return;

		//Save Current Level Name
		FString LevelName = GetWorld()->GetMapName();
		LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		SaveInstance->GameProgressData.LevelName = FName(*LevelName);


		//Save Game Data To Slot
		switch (SaveSlot)
		{
		case EEGSaveSlot::E_SaveSlot:

			UGameplayStatics::SaveGameToSlot(SaveInstance, Name_SaveSlot0, UserIndex);
			break;
		case EEGSaveSlot::E_CheckPoint:

			UGameplayStatics::SaveGameToSlot(SaveInstance, Name_CheckPointSlot, UserIndex);
			break;
		default:
			EGLOG(Error, TEXT("Save Slot input param error"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Save Game Error"));
		}

		//���Կ� ����
		
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Save"));
		//EGLOG(Error, TEXT("Load Set Move To : %s"), *SaveInstance->GameProgressData.LevelName.ToString());
}

void UEGGameInstance::LoadGame(const EEGSaveSlot SaveSlot)
{
	//������ �����ϰ� ������ ���� ��Ȳ�� LoadGame���� �ٲ��ش�.
	//�� Controller�� ������Ʈ�� ������ ���۵� �� Load ������ �������� Ȯ���ϰ�
	//Load Game�̶�� ������ �ҷ��´�
	
	/*
		Player�� BeginPlay�� ���� �������� �ε��ϱ�� �Ѵ�.
		
	*/

	

	UEGSaveGame* LoadInstance = nullptr;


	switch (SaveSlot)
	{


	case EEGSaveSlot::E_SaveSlot:

		//LoadGame ���·�
		EGameState = EEGGameState::E_LoadGame;
		UE_LOG(LogTemp, Log, TEXT("Current Game State is Load Game "));
		LoadInstance = Cast<UEGSaveGame>(UGameplayStatics::LoadGameFromSlot(Name_SaveSlot0, UserIndex));
		if (!LoadInstance)
		{
			EGLOG(Error, TEXT("Load Insatnce Failed"));
			return;
		}
		break;


	case EEGSaveSlot::E_CheckPoint:
		//Check Point ���·�
		EGameState = EEGGameState::E_Death;
		UE_LOG(LogTemp, Log, TEXT("Current Game State is Death(Check Point)"));

		LoadInstance = Cast<UEGSaveGame>(UGameplayStatics::LoadGameFromSlot(Name_CheckPointSlot, UserIndex));
		if (!LoadInstance)
		{
			EGLOG(Error, TEXT("Load Insatnce Failed"));
			return;
		}

		break;
	default:
		EGLOG(Error, TEXT("Save Slot input param error"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Load Game Error"));
		return;
	}



	if (!LoadInstance)
	{
		EGLOG(Warning, TEXT("Load instance is nullptr"));
		return;
	}



	EGLOG(Error, TEXT("Load Level : %s"), *LoadInstance->GameProgressData.LevelName.ToString());
	UGameplayStatics::OpenLevel(this,LoadInstance->GameProgressData.LevelName);
	EGLOG(Error, TEXT("Load Complete"));
	//Load ó���� ������ Player�� BeginPlay�ܰ迡�� ������ �ε带 �õ��Ѵ�
}

void UEGGameInstance::SaveOptions(float sld_Master, float sld_BGM, float sld_SE, float sld_Voice, float sld_UI, FIntPoint ScreenResoultion, EWindowMode::Type WindowMode)
{
	auto SaveInstance = NewObject<UOptionSaveGame>();
	if (!SaveInstance)return;

	SaveInstance->SetValues(sld_Master, sld_BGM, sld_SE, sld_Voice, sld_UI, ScreenResoultion, WindowMode);
	UGameplayStatics::SaveGameToSlot(SaveInstance, Name_OptionsSlot, UserIndex);
}

UOptionSaveGame* UEGGameInstance::LoadOptions()
{
	//���� ���۽� ����ƴ� �ɼ��� �ҷ��´�.
	//���� �ҷ������� �ִٸ� ���� �÷��̰� ����Ǳ� ������
	//�ɼ��� �ҷ����� �ؼ� �� �ȴ�.


	auto LoadInstance = Cast<UOptionSaveGame>(UGameplayStatics::LoadGameFromSlot(Name_OptionsSlot, UserIndex));
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("Load Insatnce Failed"));
		return nullptr;
	}



	return LoadInstance;
	

}

//loading screen�� �ҷ��´�
void UEGGameInstance::BeginLoadingScreen(const FString & MapName)
{
	
	if (!IsRunningDedicatedServer())
	{
		
	
			FLoadingScreenAttributes LoadingScreen;
			LoadingScreen.bMoviesAreSkippable = false;
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
			LoadingScreen.WidgetLoadingScreen = UI_LoadingScreeen->TakeWidget();
			//LoadingScreen.MinimumLoadingScreenDisplayTime=

			GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);

	
	
	}
}
//loading screen�� �ݴ´�
void UEGGameInstance::EndLoadingScreen(UWorld * InLoadedWorld)
{
	EGLOG(Error, TEXT("close loading screen"));
	if (UGameViewportClient* ViewportClient = GetGameViewportClient())
		ViewportClient->RemoveViewportWidgetContent(UI_LoadingScreeen->TakeWidget());

}




const TWeakObjectPtr<AEGPostProcessVolume> UEGGameInstance::GetPostProcessVolume()
{
	return PostProcessVolume;
}
TWeakObjectPtr<class AAStarFinder>UEGGameInstance::GetAStarFinder()
{
	return AStarFinder;
}

bool  UEGGameInstance::SetPostProcessVolume(TWeakObjectPtr<AEGPostProcessVolume> Object)
{
	if (!Object.IsValid())return false;

	PostProcessVolume =  Object;
	return true;
}
bool  UEGGameInstance::SetAStarFinder(TWeakObjectPtr<AAStarFinder> Object)
{
	if (!Object.IsValid())return false;

	if (AStarFinder!=nullptr)
	{
		EGLOG(Error, TEXT("AStarFinder is already Setted"));
		return false;
	}

	AStarFinder = Object;
	return true;


}
