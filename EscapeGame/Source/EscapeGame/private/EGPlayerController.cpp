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
	BindComponentsToHUD();
	EGLOG(Warning, TEXT("Controller begin play"));

	
	
	EGLOG(Warning, TEXT("Current Game Mode : %s"), *GetWorld()->GetFirstPlayerController()->GetName());
	
	FInputModeGameOnly GameOnly;
	SetInputMode(GameOnly);



	/*EGPlayer->Inventory->OnItemUpdated.BindUFunction(HUD, FName("UpdateItemes"));
	EGPlayer->Inventory->OnItemUpdated.Execute(FString("hi"),0);*/
	//TutorialUI->Test(FText::FromString(TEXT("TestTs")), FText::FromString(TEXT("notitnotif")));


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

	
	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
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

//True�� Ű���� �Է�, false�� ���콺 ���۰� Ű���� �Է�
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
1. Tutorial UI�� ����������� UI�� ���ְ� ��
2. Turorial UI�� �����ְ� ������ ���� ���̸� Pause �޴� ���
3. Tutorial UI�� �����ְ� ������ �ߴ� ������ �簳


*/
void AEGPlayerController::OnEscPressed()
{
	
	//Tutorial UI �ݱ�
	if (TutorialUI->IsInViewport())
	{
		CloseTutorialMessage();
	}

	//Pasue ȣ���ϱ�
	else if (!GetWorld()->IsPaused())
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

	//SaveInstance�� Player�� ������ �����ؾߵȴ�
	
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
		Player�� �����͸� �ҷ����� ����
		1. ��ǥ ���� �ҷ�����
		2. ���� �ҷ�����
		3. ������ ���� �ҷ�����
	*/
	EGPlayer->SetActorLocationAndRotation(LoadData.Location, LoadData.Rotation);
	EGPlayer->GetStatComponent()->LoadGameStat(LoadData.Level, LoadData.Exp, LoadData.Hp);

	//Item > 0�� ��쿡�� �ҷ��´�
	if (LoadData.n_RecoverItmes > 0)
	{
		//World�� Recover Item�� ����
		auto TempRecover = Cast<AItem_Recover>(GetWorld()->SpawnActor(AItem_Recover::StaticClass()));
		if (!TempRecover)
		{
			EGLOG(Error, TEXT("Null Item"));
			return;
		}

		EGPlayer->GetInventory()->LoadGameData(TempRecover, LoadData.n_RecoverItmes);


	}

	if (LoadData.n_CardKeys > 0)
	{
		//World�� Recover Item�� ����
		auto TempRecover = Cast<AItem_CardKey>(GetWorld()->SpawnActor(AItem_CardKey::StaticClass()));
		if (!TempRecover)
		{
			EGLOG(Error, TEXT("Null Item"));
			return;
		}

		EGPlayer->GetInventory()->LoadGameData(TempRecover, LoadData.n_CardKeys);

	}

	
	//Time �ҷ�����
	EGPlayer->GetTimeLimitComponent()->LoadTime(LoadInstance->GameProgressData.RemainTimes);
	EGPlayer->GetFuryComponent()->LoadFury(LoadData.Fury);
	EGLOG(Error, TEXT("Player Load game called"));
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


		SetInputMode(GameAndUIMode);
		bShowMouseCursor = true;
	}

}

void AEGPlayerController::CloseTutorialMessage()
{
	if (TutorialUI->IsInViewport())
	{
		TutorialUI->RemoveFromViewport();
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
}


 
