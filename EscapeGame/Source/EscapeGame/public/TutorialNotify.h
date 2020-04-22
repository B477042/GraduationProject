// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Engine/TriggerBox.h"
#include "Components/TextRenderComponent.h"
#include "TutorialNotify.generated.h"

/*
	- �÷��̾ �����ϴ� ĳ���Ͱ� ������ �۵��Ѵ�
	- ȭ�鿡 ��ũ��Ʈ�� ���� �˾� �����ش�
	- ���� �ð��� ������ ��������
	- ����� �� �ѹ��� ���ش�
	- uproperty�� �����Ϳ��� � �̺�Ʈ�� ��½�ų���� ���� �� �ְ� ���ش�
	- �̰��� actor�� 
	- AActor->ATriggerBase ->ATriggerBox
*/

//notify ���� �̺�Ʈ�� ����
UENUM()
enum class ENotifyType :int32 {
	E_None=0,
	E_MoveInput ,
	E_MouseInput,
	E_AttackInput,
	E_Jump,
	E_TrapFire,
	E_Trap_Shutter,

	E_GruntEnemy
};

UCLASS()
class ESCAPEGAME_API ATutorialNotify : public ATriggerBox
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
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
		//void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapBegin(AActor* OvelappedActor, AActor*OtherActor);
	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(AActor* OvelappedActor, AActor*OtherActor);

protected:
	//Init TextRenderer Default Value
	void initTextRenderer();
protected:
	

	UPROPERTY(EditInstanceOnly, Category = "NotifyType", meta = (ToolTip = "� Ʃ�丮�� �޽����� ��µ��� �����ݴϴ�"))
		ENotifyType NotifyType;
	UPROPERTY(VisibleInstanceOnly, Category = "TEXT", meta = (ToolTip = "3d������ ��µ� �ؽ�Ʈ"))
	UTextRenderComponent* TextRenderer;
};
