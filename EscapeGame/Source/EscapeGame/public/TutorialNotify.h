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

//������ �˷���� �ϴ��� �����ϱ� ���� enum
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
	//ENotify�� �ش�Ǵ� Message�� TutorialUI�� �ҷ����� ���ش�
	void loadTutorialMessage(class AEGPlayerController* PlayerController);

protected:
	//ENotifyType�� �����ϴ� FName���� ����
	const static TMap<ENotifyType, FName> SetOfNotifyMessage;

	UPROPERTY(EditInstanceOnly, Category = "TriggerCollision")
		UBoxComponent* BoxTrigger;
	//Root������Ʈ������ ����� ������Ʈ. �ƹ��͵� ���� �ʴ´�
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Axis;
	//�߿��� �޽������ ������ �ߴ� ��Ų��
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly,Category="Data")
	bool bIsImportant;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Data")
	FName NotifyTitle;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Data")
	ENotifyType NotifyType;
};
