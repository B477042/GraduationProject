// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "CharacterStateComponent.generated.h"

/*
	�ش� ĳ������ ���¸� �����Ѵ�.
	���´� ���������� ���� ���̴�.

	��ġ ���� ����
	InGround : ���鿡 ��� �ִ� ����
	InAir : ���鿡�� ������ ����

	������ ���� ����, ä�� ���� ���·� �� �� ���� �ʳ�?
	DamageAllowed : �������� �޴� ����
	DamageNotAllowed : �������� ���� ���ϴ� ����

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
