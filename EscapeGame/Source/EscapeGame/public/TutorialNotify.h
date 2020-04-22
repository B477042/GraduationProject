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
	- 화면에 스크립트를 대충 팝업 시켜준다
	- 일정 시간이 지나면 없어진다
	- 출력은 단 한번만 해준다
	- uproperty로 에디터에서 어떤 이벤트를 출력시킬건지 정할 수 있게 해준다
	- 이것은 actor다 
	
*/

//notify 해줄 이벤트의 종류
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
	
	//오버랩 된 엑터를 조사합니다. 만약 Player의 character가 아니라면 false
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
	//해당되는 튜토리얼 문구를 출력해줍니다
	void setInfo();

protected:
	UPROPERTY(EditInstanceOnly, Category = "TriggerCollision")
		UBoxComponent* BoxTrigger;
	//Root컴포넌트용으로 사용할 컴포넌트. 아무것도 하지 않는다
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Axis;
	UPROPERTY(EditInstanceOnly, Category = "NotifyType", meta = (ToolTip = "어떤 튜토리얼 메시지가 출력될지 보여줍니다"))
		ENotifyType NotifyType;
	UPROPERTY(VisibleInstanceOnly, Category = "TEXT", meta = (ToolTip = "3d공간에 출력될 텍스트"))
	UTextRenderComponent* TextRenderer;
};
