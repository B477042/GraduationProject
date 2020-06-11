// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerController.h"
#include "GameWidget.h"
#include "EGPlayerCharacter.h"
#include "..\public\EGPlayerController.h"
#include "DT_DataStruct.h"
#include "MySaveGame.h"
#include "Item_Recover.h"
#include "Item_CardKey.h"
#include "EGGameState.h"
#include "Engine.h"

//#include"GameStat.h"


AEGPlayerController::AEGPlayerController()
{
	
	static ConstructorHelpers::FClassFinder<UGameWidget> UI_HUD_C(TEXT("/Game/MyFolder/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable>DT_PLAYER(TEXT("DataTable'/Game/MyFolder/DataTable/DT_PlayerStat.DT_PlayerStat'"));
	if (DT_PLAYER.Succeeded())
	{
		DT_Player = DT_PLAYER.Object;
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget>UI_PAUSE_C(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_Pause.UI_Pause_C'"));
	if (UI_PAUSE_C.Succeeded())
	{
		PAUSEWidgetClass = UI_PAUSE_C.Class;
	}

	//bIsPauseCalled = false;
}

void AEGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ChangeInputMode(true);
	HUD = CreateWidget<UGameWidget>(this, HUDWidgetClass);

	//번호가 높을수록 위에 뜨는 ui 가 된다
	HUD->AddToViewport(1);

	
	//PlayerStat = Cast<UGameStat>(PlayerStat);
	//if (PlayerStat == nullptr)return;
	//HUD->BindCharacterStat(PlayerStat);
	SyncStatToHUD();
	EGLOG(Warning, TEXT("Controller begin play"));

	KeyInputTest.AddUObject(this,&AEGPlayerController::IsMoveKeyPressed);
	
	EGLOG(Warning, TEXT("Current Game Mode : %s"), *GetWorld()->GetFirstPlayerController()->GetName());
	
	FInputModeGameOnly GameOnly;
	SetInputMode(GameOnly);


	
	auto tempChara = Cast<AEGPlayerCharacter>(GetPawn());
	if (!tempChara)
	{
	
		return;
	}

	
	HUD->BindCharacterInven(tempChara->GetInventory());

	


}

void AEGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("Pause"), EInputEvent::IE_Pressed, this, &AEGPlayerController::OnGamePaused);
	InputComponent->BindAction(TEXT("KillAll"), EInputEvent::IE_Pressed, this, &AEGPlayerController::OnKillMode);

}

void AEGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EGLOG(Warning, TEXT("Controller post initialize components"));
	
}

void AEGPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);
	
	if (LoadGame())
	{
		EGLOG(Error, TEXT("Loading Complete"));
	}
	else
		EGLOG(Error, TEXT("No Save File"));

	
}

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

void AEGPlayerController::OnGamePaused()
{
	EGLOG(Warning, TEXT("TIMEEE2"));
	//Pasue 호출하기
	if (!GetWorld()->IsPaused())
	{
		//EGLOG(Warning, TEXT("TIMEEE"));
		if(!PauseUI)
		PauseUI = CreateWidget<UUserWidget>(this, PAUSEWidgetClass);
		if (!PauseUI)return;

		PauseUI->AddToViewport(3);
		SetPause(true);
	//UIInput mode로 전환
		ChangeInputMode(false);
		
		//bIsPauseCalled = true;
	}
	//Toggle하여 닫기
	else
	{

		EGLOG(Error, TEXT("Siobal"));
		ChangeInputMode(true);
		//bIsPauseCalled = false;
		SetPause(false);
		PauseUI->RemoveFromViewport();
		PauseUI->RemoveFromParent();

	}

}





void AEGPlayerController::OnKillMode()
{
	auto chara = GetCharacter();
	if (!chara)return;

	//탐지된 여러가지의 결과들
	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FDamageEvent DamageEvent;
	
	
	bool bResult = GetWorld()->OverlapMultiByChannel(OverlapResults, chara->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
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

 void AEGPlayerController::SyncStatToHUD()
 {
	 auto player = Cast<AEGPlayerCharacter>(GetCharacter());
	 if (player==nullptr)
	 {
		 EGLOG(Error, TEXT("Dynamic failed"));
		 return;
	 }
	 HUD->BindCharacterStat(player->GetStatComponent());
	
	 
 }

void AEGPlayerController::IsMoveKeyPressed()
 {
	//inputkey
	 if (IsInputKeyDown(EKeys::A))
	 {
		 EGLOG(Warning, TEXT("A Pressed"));
		 //return true;
	 }
	 else if (IsInputKeyDown(EKeys::S))
	 {
		 EGLOG(Warning, TEXT("S Pressed"));
	 }
	 else if (IsInputKeyDown(EKeys::D))
	 {
		 EGLOG(Warning, TEXT("D Pressed"));
	 }
	 else if (IsInputKeyDown(EKeys::W))
	 {
		 EGLOG(Warning, TEXT("W Pressed"));
	 }
	
	 
	// return false;
 }

const UDataTable * AEGPlayerController::GetDT_Player()
{
	return DT_Player;
}

void AEGPlayerController::SaveGame()
{
	auto SaveInstance = NewObject<UMySaveGame>();
	if (!SaveInstance)return;
	

	auto tempChara = Cast<AEGPlayerCharacter>(GetPawn());
	if (!tempChara)return;

	tempChara->GetStatComponent()->SaveGame(SaveInstance);
	
	SaveInstance->LastLocation = tempChara->GetActorLocation();
	SaveInstance->LastRotator = tempChara->GetActorRotation();


	SaveInstance->RemainTime = HUD->RemainTime;

	SaveInstance->n_RecoveryItem = tempChara->Inventory->GetAmountItem(AItem_Recover::Tag);
	SaveInstance->n_CardKey= tempChara->Inventory->GetAmountItem(AItem_CardKey::Tag);
	//SaveInstance.Level = statComp.

	SaveInstance->WorldName =  FName(*GetWorld()->GetName());

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Game Saved"));

	//SaveInstance->LoadType = ELoadType::Game;

	UGameplayStatics::SaveGameToSlot(SaveInstance, SaveInstance->SaveSlotName, SaveInstance->UserIndex);

}

bool AEGPlayerController::LoadGame()
{
	UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	if (!LoadGameInstance) { EGLOG(Error, TEXT("No Save File")); return false; }

	auto LoadType = LoadGameInstance->LoadType;

	//새로하기면 load 할 필요가 없다
	if (LoadType == ELoadType::NewGame) 
	{ 
		EGLOG(Error, TEXT("New Game!"));
		return true; 
	}

	auto tempChara = Cast<AEGPlayerCharacter>(GetPawn());
	if (!tempChara)return false;


	//HUD->LoadGame(LoadGameInstance->RemainTime);
	tempChara->GetStatComponent()->LoadGame(LoadGameInstance);
	if (LoadGameInstance->n_CardKey != -1)
	{
		auto tempKey = GetWorld()->SpawnActor<AItem_CardKey>();
		tempKey->SetActorHiddenInGame(true);
		tempChara->Inventory->AddItem(tempKey, LoadGameInstance->n_CardKey);
	}
	if (LoadGameInstance->n_RecoveryItem != -1)
	{
		auto tempItem =  GetWorld()->SpawnActor <AItem_Recover>();
		tempItem->SetActorHiddenInGame(true);
		tempChara->Inventory->AddItem(tempItem, LoadGameInstance->n_RecoveryItem);
	}
	//Title -> Load Game으로 호출된건지 검사한다. 
	//auto gameState = Cast<AEGGameState>(GetWorld()->GetGameState());
	//if (!gameState) { EGLOG(Error, TEXT("Game State is not Matched")); return false; }
	//if (!gameState->bIsLoadedGame) { return false; }
/*
	if(LoadGameInstance->LastLocation!=FVector::ZeroVector)
	tempChara->SetActorLocationAndRotation(LoadGameInstance->LastLocation, LoadGameInstance->LastRotator);*/
	
	//NextStage로 호출된 것이면 위치를 조정할 필요가 없다
	if (LoadType == ELoadType::NextStage)
	{
		EGLOG(Error, TEXT("Next Stage!"));
		return true;
	}
	
	tempChara->SetActorLocationAndRotation(LoadGameInstance->LastLocation, LoadGameInstance->LastRotator);
	return true;
	//level 여는건 title ui가 처리해야 된다.
	//UGameplayStatics::OpenLevel(this, LoadGameInstance->WorldName);



}

bool AEGPlayerController::NextStage()
{
	UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	if (!LoadGameInstance) { EGLOG(Error, TEXT("No Save File")); return false; }



	auto tempChara = Cast<AEGPlayerCharacter>(GetPawn());
	if (!tempChara)return false;


	//HUD->LoadGame(LoadGameInstance->RemainTime);
	tempChara->GetStatComponent()->LoadGame(LoadGameInstance);
	if (LoadGameInstance->n_CardKey != -1)
	{
		auto tempKey = GetWorld()->SpawnActor<AItem_CardKey>();
		tempKey->SetActorHiddenInGame(true);
		tempChara->Inventory->AddItem(tempKey, LoadGameInstance->n_CardKey);
	}
	if (LoadGameInstance->n_RecoveryItem != -1)
	{
		auto tempItem = GetWorld()->SpawnActor <AItem_Recover>();
		tempItem->SetActorHiddenInGame(true);
		tempChara->Inventory->AddItem(tempItem, LoadGameInstance->n_RecoveryItem);
	}
	//tempChara->SetActorLocationAndRotation(LoadGameInstance->LastLocation, LoadGameInstance->LastRotator);
	return true;
}

 
