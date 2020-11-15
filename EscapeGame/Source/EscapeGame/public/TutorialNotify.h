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

////무엇을 알려줘야 하는지 설정하기 위한 enum
//UENUM()
//enum class ENotifyType :int32 {
//	E_None = 0,
//	E_MoveInput,
//	E_MouseInput,
//	E_AttackInput,
//	E_Jump,
//	E_TrapFire,
//	E_Trap_Shutter,
//	E_Claymore,
//	E_HealBox,
//	E_Lightning,
//	E_GruntEnemy,
//	E_ChargeAttack
//};

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
	

protected:
	UPROPERTY(EditInstanceOnly, Category = "TriggerCollision")
		UBoxComponent* BoxTrigger;
	//Root컴포넌트용으로 사용할 컴포넌트. 아무것도 하지 않는다
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Axis;
	//중요한 메시지라면 게임을 중단 시킨다
	UPROPERTY(VisibleAnywhere,Category="Data")
	bool bIsImportant;
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Data")
		FString MessageTag;

	
};
