// Fill out your copyright notice in the Description page of Project Settings.


//#include"GameStat.h"


#include "Actor/Character/EGPlayerController.h"

#include "AbilitySystemComponent.h"
#include "Actor/Character/EGPlayerCharacter.h"
#include "Actor/Item/Item_CardKey.h"
#include "Actor/Item/Item_Recover.h"
#include "Blueprint/UserWidget.h"
#include "Component/Component_TimeLimit.h"
#include "Component/StatComponent_Player.h"
#include "Data/DT_DataStruct.h"
#include "GameAbility/Component_Fury.h"
#include "GameAbility/Component_Inventory.h"
#include "GameFramework/Character.h"
#include "GameSystem/Tutorial/TutorialLogWidget.h"
#include "UI/GameWidget.h"
#include "UnrealCore/EGGameInstance.h"
#include "UnrealCore/EGPlayerState.h"
#include "UnrealCore/SaveGame/EGSaveGame.h"

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

	//��ȣ�� �������� ���� �ߴ� ui �� �ȴ�
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

	// PlayerState에서 GAS를 가져오기
	TObjectPtr<AEGPlayerState> egPlayerState = GetEGPlayerState();
	TObjectPtr<AGameCharacterBase> gameCharacter = Cast<AGameCharacterBase>(aPawn);
	if (egPlayerState && gameCharacter)
	{
		TObjectPtr<UEGCharacterAttributeSet> playerStateAttribute = egPlayerState->GetAttributeSet();
		TObjectPtr<UAbilitySystemComponent> asc = egPlayerState->GetAbilitySystemComponent();

		gameCharacter->SetAbilitySystemComponent(asc);
		gameCharacter->SetAttributeSet(playerStateAttribute);

		// Reset ASC Owner
		asc->InitAbilityActorInfo(this,aPawn);

		
		
	}
	
	
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

AEGPlayerState* AEGPlayerController::GetEGPlayerState()
{
	if (!PlayerState)
	{
		EGLOG(Error, TEXT("PlayerState is null"));
		return nullptr;
	}
	return Cast<AEGPlayerState>(PlayerState);
}


/*
1. Tutorial UI�� ����������� UI�� ���ְ� ��
2. Turorial UI�� �����ְ� ������ ���� ���̸� Pause �޴� ���
3. Tutorial UI�� �����ְ� ������ �ߴ� ������ �簳


*/
void AEGPlayerController::OnEscPressed()
{
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}

	//Tutorial UI �ݱ�
	if (TutorialUI->IsInViewport())
	{
		CloseTutorialMessage();
	}
	//���� ���¸� �����
	if (DeadUI)
	{
		return;
	}


	//Pasue ȣ���ϱ�
	else if (!World->IsPaused())
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
		PauseUI->RemoveFromParent();
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

	//Ž���� ���������� �����
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
	 HUD->RemoveFromParent();
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

	 HUD->RemoveFromParent();
	 DeadUI->AddToViewport(VP_Dead);
	 //UIInput mode�� ��ȯ
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

	 HUD->BindCharacterInventory(EGPlayer->GetInventory());
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
		//World�� Recover Item�� ����
		auto TempRecover = Cast<AItem_CardKey>(World->SpawnActor(AItem_CardKey::StaticClass()));
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
	TutorialUI->RemoveFromParent();
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


 
