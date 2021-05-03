// Fill out your copyright notice in the Description page of Project Settings.

#include "EGPlayerController.h"
#include "GameWidget.h"
#include "EGPlayerCharacter.h"
#include "..\public\EGPlayerController.h"
#include "DT_DataStruct.h"
#include "EGSaveGame.h"
#include "Item_Recover.h"
#include "Item_CardKey.h"
#include "EGGameState.h"
#include "Engine.h"
#include "EGGameInstance.h"
#include "TutorialWidget.h"

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
	static ConstructorHelpers::FClassFinder<UTutorialWidget>UI_TUTORIAL_C(TEXT("WidgetBlueprint'/Game/MyFolder/UI/UI_Tutorial.UI_Tutorial_C'"));
	if (UI_TUTORIAL_C.Succeeded())
	 {
		TUTOWidgetClass = UI_TUTORIAL_C.Class;
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

	

	//bIsPauseCalled = false;
}

void AEGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ChangeInputMode(true);

	HUD = CreateWidget<UGameWidget>(this, HUDWidgetClass);
	TutorialUI = CreateWidget<UTutorialWidget>(this, TUTOWidgetClass);
	







	//��ȣ�� �������� ���� �ߴ� ui �� �ȴ�
	HUD->AddToViewport(VP_HUD);
	//TutorialUI->AddToViewport(VP_Tutorial);
	
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
	
	//TutorialUI->Test(FText::FromString(TEXT("TestTs")), FText::FromString(TEXT("notitnotif")));


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
	
	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Game Instance is not UEGGameInstance"));
		return;
	}
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AEGPlayerController::SaveGame);


}

void AEGPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);
	
	EGLOG(Error, TEXT("Player con Possess"));
	

	
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
	
	//Pasue ȣ���ϱ�
	if (!GetWorld()->IsPaused())
	{
		//EGLOG(Warning, TEXT("TIMEEE"));
		if(!PauseUI)
		PauseUI = CreateWidget<UUserWidget>(this, PAUSEWidgetClass);
		if (!PauseUI)return;

		PauseUI->AddToViewport(VP_Pause);
		SetPause(true);
	//UIInput mode�� ��ȯ
		ChangeInputMode(false);
	
		//bIsPauseCalled = true;
	}
	//Toggle�Ͽ� �ݱ�
	else
	{

		
		ChangeInputMode(true);
		//bIsPauseCalled = false;
		SetPause(false);
		PauseUI->RemoveFromViewport();
		PauseUI->RemoveFromParent();

	}

}

void AEGPlayerController::OnEnterPressed()
{

}





void AEGPlayerController::OnKillMode()
{
	auto chara = GetCharacter();
	if (!chara)return;

	//Ž���� ���������� �����
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

	auto egPlayer = Cast<AEGPlayerCharacter>(GetPawn());
	if (!egPlayer)
	{
		EGLOG(Error, TEXT("Casting failed in player controller"));
		return;
	}

	//SaveInstance�� Player�� ������ �����ؾߵȴ�
	
	FPlayerData playerData;
	playerData.ActorName= egPlayer->GetName();
	playerData.Location = egPlayer->GetActorLocation();
	playerData.Rotation = egPlayer->GetActorRotation();
	playerData.Level = egPlayer->GetStatComponent()->GetLevel();
	playerData.Exp = egPlayer->GetStatComponent()->GetExp();
	playerData.Hp = egPlayer->GetStatComponent()->GetHP();
	playerData.n_CardKeys = egPlayer->GetInventory()->GetAmountItem(AItem_CardKey::Tag);
	playerData.n_RecoverItmes = egPlayer->GetInventory()->GetAmountItem(AItem_Recover::Tag);

	SaveInstance->D_Player=playerData;


}

void AEGPlayerController::LoadGame(UEGSaveGame* LoadInstance)
{
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("Load Instance is not vaild"));
		return;

	}

	auto egPlayer = Cast<AEGPlayerCharacter>(GetPawn());
	if (!egPlayer)
	{
		EGLOG(Error, TEXT("Casting failed in player controller"));
		return;
	}

	auto loadData = LoadInstance->D_Player;

	/*
		Player�� �����͸� �ҷ����� ����
		1. ��ǥ ���� �ҷ�����
		2. ���� �ҷ�����
		3. ������ ���� �ҷ�����
	*/
	egPlayer->SetActorLocationAndRotation(loadData.Location, loadData.Rotation);
	egPlayer->GetStatComponent()->LoadGameStat(loadData.Level, loadData.Exp, loadData.Hp);

	//Item > 0�� ��쿡�� �ҷ��´�
	if (loadData.n_RecoverItmes > 0)
	{
		//World�� Recover Item�� ����
		auto tempRecover = Cast<AItem_Recover>(GetWorld()->SpawnActor(AItem_Recover::StaticClass()));
		if (!tempRecover)
		{
			EGLOG(Error, TEXT("Null Item"));
			return;
		}

		egPlayer->GetInventory()->LoadGameData(tempRecover, loadData.n_RecoverItmes);


	}

	if (loadData.n_CardKeys > 0)
	{
		//World�� Recover Item�� ����
		auto tempRecover = Cast<AItem_CardKey>(GetWorld()->SpawnActor(AItem_CardKey::StaticClass()));
		if (!tempRecover)
		{
			EGLOG(Error, TEXT("Null Item"));
			return;
		}

		egPlayer->GetInventory()->LoadGameData(tempRecover, loadData.n_CardKeys);

	}



}

//�Ѿ���� enum(uint8)�� �������� �� ���� �����͸� �ҷ��� Ʃ�丮�������� �ٹδ�
void AEGPlayerController::ShowTutorialMessage(uint8 TutorialMessage)
{
	auto tempData = DT_Tutorial->FindRow<FTutorialDataTable>(FName(*FString::FormatAsNumber(TutorialMessage)), FString(""));
	if (tempData)
	{
		
		if (!TutorialUI->IsInViewport())
		TutorialUI->AddToViewport(VP_Tutorial);

		TutorialUI->ReceiveMessage(tempData->NotifyTittle, FText::FromString(tempData->Describe),tempData->GifPath);

	}

}

void AEGPlayerController::CloseTutorialMessage()
{
	if (TutorialUI->IsInViewport())
	{
		TutorialUI->RemoveFromViewport();
	}
}


 
