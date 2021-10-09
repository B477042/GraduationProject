// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerController.h"
#include "GameWidget.h"
#include "EGPlayerCharacter.h"
#include "DT_DataStruct.h"
#include "EGSaveGame.h"
#include "Item_Recover.h"
#include "Item_CardKey.h"
#include "EGGameState.h"
#include "Engine.h"
#include "EGGameInstance.h"
#include "TutorialLogWidget.h"
#include "SaveInfoWidget.h"

//#include"GameStat.h"


AEGPlayerController::AEGPlayerController()
{

	static ConstructorHelpers::FClassFinder<UGameWidget> UI_HUD_C(TEXT("/Game/MyFolder/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{

		HUDWidgetClass = UI_HUD_C.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget>UI_PAUSE_C(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_Pause.UI_Pause_C'"));
	if (UI_PAUSE_C.Succeeded())
	{
		PAUSEWidgetClass = UI_PAUSE_C.Class;
	}
	//static ConstructorHelpers::FClassFinder<UTutorialWidget>UI_TUTORIAL_C(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_Tutorial.UI_Tutorial_C'"));
	//if (UI_TUTORIAL_C.Succeeded())
	// {
	//	TUTOWidgetClass = UI_TUTORIAL_C.Class;
	//}
	
	static ConstructorHelpers::FClassFinder<UTutorialLogWidget>UI_TUTORIAL_C(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_MessageTypeLog.UI_MessageTypeLog_C'"));
	if (UI_TUTORIAL_C.Succeeded())
	{
		TUTOWidgetClass = UI_TUTORIAL_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget>UI_DEAD_C(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_Dead.UI_Dead_C'"));
	if (UI_DEAD_C.Succeeded())
	{
		DeadWidgetClass = UI_DEAD_C.Class;
	}



	static ConstructorHelpers::FObjectFinder<UDataTable>DT_PLAYER(TEXT("DataTable'/Game/MyFolder/DataTable/DT_PlayerStat.DT_PlayerStat'"));
	if (DT_PLAYER.Succeeded())
	{
		DT_Player = DT_PLAYER.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_TUTO(TEXT("DataTable'/Game/MyFolder/DataTable/DT_TutorialNotifyMessages.DT_TutorialNotifyMessages'"));
	if (DT_TUTO.Succeeded())
	{
		DT_Tutorial = DT_TUTO.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundWave>PopUpSound(TEXT("SoundWave'/Game/MyFolder/Sound/UI/cncl07.cncl07'"));
	if (PopUpSound.Succeeded())
	{
		SFX_TutorialPop = PopUpSound.Object;

	}


}

void AEGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ChangeInputMode(true);
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}

	HUD = CreateWidget<UGameWidget>(this, HUDWidgetClass);
	TutorialUI = CreateWidget<UTutorialLogWidget>(this, TUTOWidgetClass);

	//번호가 높을수록 위에 뜨는 ui 가 된다
	HUD->AddToViewport(VP_HUD);
	//TutorialUI->AddToViewport(VP_Tutorial);
	
	//PlayerStat = Cast<UGameStat>(PlayerStat);
	//if (PlayerStat == nullptr)return;
	//HUD->BindCharacterStat(PlayerStat);
	BindComponentsToHUD();
	EGLOG(Warning, TEXT("Controller begin play"));

	
	
	EGLOG(Warning, TEXT("Current Game Mode : %s"), *World->GetFirstPlayerController()->GetName());
	
	FInputModeGameOnly GameOnly;
	SetInputMode(GameOnly);



	
}

void AEGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Pause"), EInputEvent::IE_Pressed, this, &AEGPlayerController::OnEscPressed);
	InputComponent->BindAction(TEXT("KillAll"), EInputEvent::IE_Pressed, this, &AEGPlayerController::OnKillMode);

}

void AEGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EGLOG(Warning, TEXT("Controller post initialize components"));
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}
	
	auto GameInstance = Cast<UEGGameInstance>(World->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Game Instance is not UEGGameInstance"));
		return;
	}
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AEGPlayerController::SaveGame);
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AEGPlayerController::LoadGame);
	
}

void AEGPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);
	
	EGLOG(Log, TEXT("Player con Possess"));
	

	
}

//True면 키보드 입력, false면 마우스 조작과 키보드 입력
void AEGPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(GameAndUIMode);
	//SetInputMode(GameInputMode);
		bShowMouseCursor = true;
	}

}



/*
1. Tutorial UI가 띄워져있으면 UI를 꺼주고 끝
2. Turorial UI가 꺼져있고 게임이 진행 중이면 Pause 메뉴 출력
3. Tutorial UI가 꺼져있고 게임이 중단 됐으면 재개


*/
void AEGPlayerController::OnEscPressed()
{
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}

	//Tutorial UI 닫기
	if (TutorialUI->IsInViewport())
	{
		CloseTutorialMessage();
	}
	//죽은 상태면 미출력
	if (DeadUI)
	{
		return;
	}


	//Pasue 호출하기
	else if (!World->IsPaused())
	{
		//EGLOG(Warning, TEXT("TIMEEE"));
		if(!PauseUI)
		PauseUI = CreateWidget<UUserWidget>(this, PAUSEWidgetClass);
		if (!PauseUI)return;

		PauseUI->AddToViewport(VP_Pause);
		SetPause(true);
	//UIInput mode로 전환
		ChangeInputMode(false);
	
		//bIsPauseCalled = true;
	}
	//Toggle하여 닫기
	else
	{
		ChangeInputMode(true);
		//bIsPauseCalled = false;
		SetPause(false);
		PauseUI->RemoveFromViewport();
		PauseUI->RemoveFromParent();

	}

}





void AEGPlayerController::OnKillMode()
{
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}
	auto chara = GetCharacter();
	if (!chara)return;

	//탐지된 여러가지의 결과들
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FDamageEvent DamageEvent;
	
	
	bool bResult = World->OverlapMultiByChannel(OverlapResults, chara->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(10000.0f), CollisionQueryParam);
	if (bResult)
	{
		for (auto it : OverlapResults)
		{
			it.GetActor()->TakeDamage(1000.0f, DamageEvent, this, this);
			//EGLOG(Error, TEXT("Additional Damage To : %s"), *it.GetActor()->GetName());
		}
	}


	
}



 UGameWidget* AEGPlayerController::GetHUDWidget() const
{
	return HUD;
}

 void AEGPlayerController::OnCineamticStart()
 {
	 HUD->RemoveFromViewport();
	 DisableInput(this);
 }



 void AEGPlayerController::OnCineamticEnd()
 {
	 HUD->AddToViewport(VP_HUD);
	 EnableInput(this);
 }

 void AEGPlayerController::OnPlayerDead()
 {
	 DeadUI = CreateWidget< UUserWidget >(this, DeadWidgetClass);

	 HUD->RemoveFromViewport();
	 DeadUI->AddToViewport(VP_Dead);
	 //UIInput mode로 전환
	 ChangeInputMode(false);
	 SetPause(true);
 }

 void AEGPlayerController::BindComponentsToHUD()
 {
	 auto EGPlayer = Cast<AEGPlayerCharacter>(GetCharacter());
	 if (EGPlayer ==nullptr)
	 {
		 EGLOG(Error, TEXT("Dynamic failed"));
		 return;
	 }
	 HUD->BindCharacterStat(EGPlayer->GetStatComponent());

	 HUD->BindCharacterInven(EGPlayer->GetInventory());
	 HUD->BindCharacterFury(EGPlayer->GetFuryComponent());
	 HUD->BindCharacterTimeLimit(EGPlayer->GetTimeLimitComponent());
	 HUD->BindCharacterStamina(EGPlayer->GetStaminaComponenet());
 }


const UDataTable * AEGPlayerController::GetDT_Player()
{
	return DT_Player;
}




bool AEGPlayerController::NextStage()
{
	


	auto tempChara = Cast<AEGPlayerCharacter>(GetPawn());
	if (!tempChara)return false;


	
	//tempChara->SetActorLocationAndRotation(LoadGameInstance->LastLocation, LoadGameInstance->LastRotator);
	return true;
}


void AEGPlayerController::SaveGame(UEGSaveGame* SaveInstance)
{
	
	if (!SaveInstance)
	{
		EGLOG(Error, TEXT("Save Instance is Not Vaild"));
		return;
	}

	auto EGPlayer = Cast<AEGPlayerCharacter>(GetPawn());
	if (!EGPlayer)
	{
		EGLOG(Error, TEXT("Casting failed in player controller"));
		return;
	}

	//SaveInstance에 Player의 정보를 저장해야된다
	
	FPlayerData playerData;
	playerData.ActorName= EGPlayer->GetName();
	playerData.Location = EGPlayer->GetActorLocation();
	playerData.Rotation = EGPlayer->GetActorRotation();
	playerData.Level = EGPlayer->GetStatComponent()->GetLevel();
	playerData.Exp = EGPlayer->GetStatComponent()->GetExp();
	playerData.Hp = EGPlayer->GetStatComponent()->GetHP();
	playerData.n_CardKeys = EGPlayer->GetInventory()->GetAmountItem(AItem_CardKey::Tag);
	playerData.n_RecoverItmes = EGPlayer->GetInventory()->GetAmountItem(AItem_Recover::Tag);

	SaveInstance->D_Player=playerData;
	SaveInstance->GameProgressData.RemainTimes = EGPlayer->GetTimeLimitComponent()->GetCurrentRemainTime();

	EGLOG(Error, TEXT("Player SAve game called"));

}

void AEGPlayerController::LoadGame(const UEGSaveGame* LoadInstance)
{
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("Load Instance is not vaild"));
		return;

	}

	auto EGPlayer = Cast<AEGPlayerCharacter>(GetPawn());
	if (!EGPlayer)
	{
		EGLOG(Error, TEXT("Casting failed in player controller"));
		return;
	}

	auto LoadData = LoadInstance->D_Player;

	/*
		Player의 데이터를 불러오는 과정
		1. 좌표 정보 불러오기
		2. 스텟 불러오기
		3. 아이템 갯수 불러오기
	*/
	EGPlayer->SetActorLocationAndRotation(LoadData.Location, LoadData.Rotation);
	EGPlayer->GetStatComponent()->LoadGameStat(LoadData.Level, LoadData.Exp, LoadData.Hp);

	//Item > 0일 경우에만 불러온다
	if (LoadData.n_RecoverItmes > 0)
	{
		//World에 Recover Item을 스폰
		auto TempRecover = Cast<AItem_Recover>(World->SpawnActor(AItem_Recover::StaticClass()));
		if (!TempRecover)
		{
			EGLOG(Error, TEXT("Null Item"));
			return;
		}

		EGPlayer->GetInventory()->LoadGameData(TempRecover, LoadData.n_RecoverItmes);


	}

	if (LoadData.n_CardKeys > 0)
	{
		//World에 Recover Item을 스폰
		auto TempRecover = Cast<AItem_CardKey>(World->SpawnActor(AItem_CardKey::StaticClass()));
		if (!TempRecover)
		{
			EGLOG(Error, TEXT("Null Item"));
			return;
		}

		EGPlayer->GetInventory()->LoadGameData(TempRecover, LoadData.n_CardKeys);

	}

	
	//Time 불러오기
	EGPlayer->GetTimeLimitComponent()->LoadTime(LoadInstance->GameProgressData.RemainTimes);
	EGPlayer->GetFuryComponent()->LoadFury(LoadData.Fury);


	EGLOG(Error, TEXT("Player Load game called"));
}

//넘어오는 enum(uint8)을 기준으로 그 열의 데이터를 불러와 튜토리얼위젯을 꾸민다
void AEGPlayerController::ShowTutorialMessage(uint8 TutorialMessage)
{
	auto tempData = DT_Tutorial->FindRow<FTutorialDataTable>(FName(*FString::FormatAsNumber(TutorialMessage)), FString(""));
	if (!tempData)
	{
		EGLOG(Error, TEXT(" Data Load FAiled"));
		return;
	}

		
	if (!TutorialUI->IsInViewport())
	TutorialUI->AddToViewport(VP_Tutorial);

	FText NotifyTittle = tempData->NotifyTittle;
	FText NotifyDescribe = FText::FromString(tempData->Describe);

	TutorialUI->ReceiveMessage(NotifyTittle,NotifyDescribe );

	//Play Sound

	auto const World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is nullptr"));
		return;
	}

	UGameplayStatics::PlaySound2D(this,SFX_TutorialPop);



	//SetInputMode(GameAndUIMode);
	//bShowMouseCursor = true;
	//auto World = GetWorld();
	//if (!World)
	//{
	//	EGLOG(Error, TEXT("World is null"));
	//	return;
	//}

	////Pause Game
	//if (!World->IsPaused())
	//{
	//	SetPause(true);
	//}


	

}

void AEGPlayerController::CloseTutorialMessage()
{
	if (!TutorialUI->IsInViewport())
	{
		EGLOG(Log, TEXT("Close Failed"));
		return;
	}
	TutorialUI->RemoveFromViewport();
	SetInputMode(GameInputMode);
	bShowMouseCursor = false;
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}

	//UnPause Game
	if (World->IsPaused())
	{
		SetPause(false);
	}


}


 
