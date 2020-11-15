// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
//#include "Engine/TriggerBox.h"
#include "Kismet/KismetMathLibrary.h"

#include "TutorialNotify.generated.h"

/*
	- �÷��̾ �����ϴ� ĳ���Ͱ� ������ �۵��Ѵ�
	
	- ���� �ð��� ������ ��������
	
	- uproperty�� �����Ϳ��� � �̺�Ʈ�� ��½�ų���� ���� �� �ְ� ���ش�
	
*/

////������ �˷���� �ϴ��� �����ϱ� ���� enum
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
	//Root������Ʈ������ ����� ������Ʈ. �ƹ��͵� ���� �ʴ´�
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Axis;
	//�߿��� �޽������ ������ �ߴ� ��Ų��
	UPROPERTY(VisibleAnywhere,Category="Data")
	bool bIsImportant;
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Data")
		FString MessageTag;

	
};
