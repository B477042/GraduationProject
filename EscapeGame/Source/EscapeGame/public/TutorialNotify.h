// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
//#include "Engine/TriggerBox.h"
#include "Kismet/KismetMathLibrary.h"

#include "TutorialNotify.generated.h"

/*
	- 플레이어가 조종하는 캐릭터가 들어오면 작동한다
	
	- Close를 누르거나 범위를 벗어나면 사라진다

	- 각 객체는 자신에게 맞는 데이터를 불러와서 그 데이터로 위젯을 만들어서 뷰포트에 올려준다
	
	- widget이 에러 때문에 생성이 안 돼서 bp로 파생시킨다
*/

//무엇을 알려줘야 하는지 설정하기 위한 enum
UENUM(BlueprintType)
enum class ENotifyType :uint8 
{

	E_None=0 UMETA(DisplayName = "None"),
	E_AttackInput UMETA(DisplayName = "AttackInput"),
	E_ChargeAttack UMETA(DisplayName = "ChargeAttack"),
	E_Claymore UMETA(DisplayName = "Claymore"),
	E_FireBallTrap UMETA(DisplayName = "FireBallTrap"),
	E_HealBox UMETA(DisplayName = "HealBox"),
	E_GameRule UMETA(DisplayName = "Game Rule"),
	E_Jump UMETA(DisplayName = "Jump"),
	E_Lightning UMETA(DisplayName = "Lightning"),
	E_MoveInput UMETA(DisplayName = "MoveInput"),
	E_GoldenGate UMETA(DisplayName = "Golden Gate"),
	E_SubBattery UMETA(DisplayName = "SubBattery"),
	E_GruntEnemy UMETA(DisplayName = "GruntEnemy"),
	E_Gunner UMETA(DisplayName = "Gunner"),
	E_Boss UMETA(DisplayName = "Boss"),
	E_Guard UMETA(DisplayName = "Guard"), 
	E_Sprint UMETA(DisplayName = "Sprint"),
	E_ShutterTrap UMETA(DisplayName = "ShutterTrap")
	
	
	
	

	

};

UCLASS()
class ESCAPEGAME_API ATutorialNotify : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialNotify();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
	
	
public:	
	

	
	UFUNCTION()
	void OnOverlapBegin(AActor * OvelappedActor, AActor * OtherActor);
	
	UFUNCTION()
	void OnOverlapEnd(AActor * OvelappedActor, AActor * OtherActor);

protected:
	
	UFUNCTION()
	void SaveGame(class UEGSaveGame* SaveInstance);
	UFUNCTION()
	void LoadGame(const class UEGSaveGame* LoadInstance);

	void initBoxComponent();

	////Load Tutorial widget datas
	//UFUNCTION(BlueprintCallable)
	//	void LoadTutorialData(FTutorialDataTable& Input);

protected:
	//ENotifyType에 대응하는 FName들의 집합
	UPROPERTY(BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = true))
	 TMap<ENotifyType, FName> SetOfTypesOfNotifications;
	//const static TMap<FName, FString>SetOfNotifyMessages;


	UPROPERTY(EditInstanceOnly, Category = "TriggerCollision", meta = (AllowPrivateAccess = true))
		UBoxComponent* BoxTrigger;
	//Root컴포넌트용으로 사용할 컴포넌트. 아무것도 하지 않는다
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Axis;
	//중요한 메시지라면 게임을 중단 시킨다
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly,Category="Data", meta = (AllowPrivateAccess = true))
	bool bIsImportant;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Data", meta = (AllowPrivateAccess = true))
	FName NotifyTitle;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Data", meta = (AllowPrivateAccess = true))
	ENotifyType NotifyType;


	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = true))
		TSubclassOf<class UUserWidget>TutoWidgetClass;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess = true))
	class  UUserWidget* TutoWidget;*/
UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = true))
		class UDataTable* DT_Tutorial;

};
