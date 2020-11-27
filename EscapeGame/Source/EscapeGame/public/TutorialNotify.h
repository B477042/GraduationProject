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
	
	- 일정 시간이 지나면 없어진다
	
	- uproperty로 에디터에서 어떤 이벤트를 출력시킬건지 정할 수 있게 해준다
	
*/

//무엇을 알려줘야 하는지 설정하기 위한 enum
UENUM(BlueprintType)
enum class ENotifyType :uint8 
{

	E_None=0 UMETA(DisplayName = "None"),
	E_HUD UMETA(DisplayName = "HUD"),
	E_MoveInput UMETA(DisplayName = "MoveInput"),
	E_MouseInput UMETA(DisplayName = "MouseInput"),
	E_AttackInput UMETA(DisplayName = "AttackInput"),
	E_Jump UMETA(DisplayName = "Jump"),
	E_FireBallTrap UMETA(DisplayName = "FireBallTrap"),
	E_ShutterTrap UMETA(DisplayName = "ShutterTrap"),
	E_Claymore UMETA(DisplayName = "Claymore"),
	E_HealBox UMETA(DisplayName = "HealBox"),
	E_Lightning UMETA(DisplayName = "Lightning"),
	E_GruntEnemy UMETA(DisplayName = "GruntEnemy"),
	E_ChargeAttack UMETA(DisplayName = "ChargeAttack")

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
	//ENotify에 해당되는 Message를 TutorialUI가 불러오게 해준다
	void loadTutorialMessage(class AEGPlayerController* PlayerController);

protected:
	//ENotifyType에 대응하는 FName들의 집합
	const static TMap<ENotifyType, FName> SetOfNotifyMessage;

	UPROPERTY(EditInstanceOnly, Category = "TriggerCollision")
		UBoxComponent* BoxTrigger;
	//Root컴포넌트용으로 사용할 컴포넌트. 아무것도 하지 않는다
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Axis;
	//중요한 메시지라면 게임을 중단 시킨다
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly,Category="Data")
	bool bIsImportant;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Data")
	FName NotifyTitle;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Data")
	ENotifyType NotifyType;
};
