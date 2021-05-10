// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EGSaveGame.h"
#include "OptionSaveGame.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "EGGameInstance.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadGamePhase, const UEGSaveGame*, LoadInstance );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGamePhase, UEGSaveGame*, SaveInstance);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOptionLoad,void);

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
	virtual void Init()override;

	UFUNCTION(BlueprintCallable)
		void SaveGame();
	UFUNCTION(BlueprintCallable)
		void LoadGame();
	UFUNCTION(BlueprintCallable)
		void SaveOptions(float sld_Master,float sld_BGM,float sld_SE,float sld_Voice,float sld_UI,FIntPoint ScreenResoultion,EWindowMode::Type WindowMode);
	UFUNCTION(BlueprintCallable)
		class UOptionSaveGame* LoadOptions();
	//Loading Screen
	UFUNCTION()
		virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
		virtual void EndLoadingScreen(UWorld* InLoadedWorld);


	const FString GetSaveSlotName() { return SaveSlotName; }
	const int32 GetSavedUserIndex() { return UserIndex; }
	


	//Player가 BeginPlay를 호출할때 실행될 것. 모든 엑터들은 자신의 정보를 불러온다
	//PostInitiliazeComponents에서 함수 등록
	FOnLoadGamePhase OnLoadGamePhaseDelegate;

	//Save Game이 호출되면 실행된다
	FOnSaveGamePhase OnSaveGamePhaseDelegate;
 
	bool bIsDebugMode;

	const TWeakObjectPtr<class AEGPostProcessVolume> GetPostProcessVolume();
	TWeakObjectPtr<class AAStarFinder>GetAStarFinder();
	bool SetPostProcessVolume(class AEGPostProcessVolume* Object);
	bool SetAStarFinder(class AAStarFinder* Object);



	FStreamableManager StreamableManager;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget>LoadingScreenWidgetClass;
	//Game의 상태. Save file을 어디까지 불러올지 확인하는데 활용
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Data")
		EEGGameState EGameState;
private:
	FString SaveSlotName;
	FString OptionsSlotName;
	int32 UserIndex;

	TWeakObjectPtr<class AEGPostProcessVolume> PostProcessVolume;

	TWeakObjectPtr<class AAStarFinder>AStarFinder;
	
	UPROPERTY(BlueprintReadWrite, Category = "Loading Screen", meta = (AllowPrivateAccess = true))
		class UUserWidget* UI_LoadingScreeen;

};
