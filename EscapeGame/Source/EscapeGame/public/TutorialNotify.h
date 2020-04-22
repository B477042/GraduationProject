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
	- ȭ�鿡 ��ũ��Ʈ�� ���� �˾� �����ش�
	- ���� �ð��� ������ ��������
	- ����� �� �ѹ��� ���ش�
	- uproperty�� �����Ϳ��� � �̺�Ʈ�� ��½�ų���� ���� �� �ְ� ���ش�
	- �̰��� actor�� 
	
*/

//notify ���� �̺�Ʈ�� ����
UENUM()
enum class ENotifyType :int32 {
	E_None = 0,
	E_MoveInput,
	E_MouseInput,
	E_AttackInput,
	E_Jump,
	E_TrapFire,
	E_Trap_Shutter,
	E_Claymore,
	E_HealBox,
	E_Lightning,
	E_GruntEnemy,
	E_ChargeAttack
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
	
	//������ �� ���͸� �����մϴ�. ���� Player�� character�� �ƴ϶�� false
	bool checkOverlappedActor(AActor* Other);
public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	
	UFUNCTION()
	void OnOverlapBegin(AActor* OvelappedActor, AActor*OtherActor);
	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(AActor* OvelappedActor, AActor*OtherActor);

protected:
	//Init TextRenderer Default Value
	void initTextRenderer();
	void initBoxComponent();
	//�ش�Ǵ� Ʃ�丮�� ������ ������ݴϴ�
	void setInfo();

protected:
	UPROPERTY(EditInstanceOnly, Category = "TriggerCollision")
		UBoxComponent* BoxTrigger;
	//Root������Ʈ������ ����� ������Ʈ. �ƹ��͵� ���� �ʴ´�
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Axis;
	UPROPERTY(EditInstanceOnly, Category = "NotifyType", meta = (ToolTip = "� Ʃ�丮�� �޽����� ��µ��� �����ݴϴ�"))
		ENotifyType NotifyType;
	UPROPERTY(VisibleInstanceOnly, Category = "TEXT", meta = (ToolTip = "3d������ ��µ� �ؽ�Ʈ"))
	UTextRenderComponent* TextRenderer;
};
