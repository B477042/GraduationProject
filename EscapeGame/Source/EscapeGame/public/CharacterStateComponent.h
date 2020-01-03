// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "CharacterStateComponent.generated.h"

/*
	해당 캐릭터의 상태를 정의한다.
	상태는 여러가지가 있을 것이다.

	위치 관련 상태
	InGround : 지면에 닿고 있는 상태
	InAir : 지면에서 떨어진 상태

	데미지 관련 상태, 채력 관련 상태로 볼 수 있지 않나?
	DamageAllowed : 데미지를 받는 상태
	DamageNotAllowed : 데미지를 받지 못하는 상태

*/

//UENUM(/*BlueprintType*/)
//	enum class EPositionState
//	{
//		EInGround UMETA(DisplayName = "InGround") = 0,
//		EInAir UMETA(DisplayName = "InAir")
//	};
//
//
//UENUM(/*BlueprintType*/)
//enum class EDamageableState
//{
//	EDamageAllowed UMETA(DisplayName = "DmageAllowed")=0,
//	EDamageNotAllowed UMETA(DisplayName = "DmageNotAllowed")
//};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		EPositionState PositionState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		EDamageableState DamageableState;
	*/	
};
