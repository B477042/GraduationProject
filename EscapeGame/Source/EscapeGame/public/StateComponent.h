// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

/*

	Anim�� �����ϴµ� ������ �� �� �ִ� ������Ʈ
	���¸� �����Ѵ�.
	�Է��� �����ϰų� Ǯ���ְų�
	���� ���� ���¸� �ٲ��ش�
	Stat ������Ʈ�� �ִ� ��ɵ��� �Űܿ´�
	

	2020 05 14 Stat Comp�� ���� �ڵ带 Ǯ���ش�

*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateComponent();

	bool IsAttacking()const;
	//Set Actor Can't Move Around using MinWalkingSpeed
	void SetDontMove();

	//Set Actor Speed To MaxRunningSpeed
	void SetRunning();
	//Set Actor Speed To MaxWalingSpeed
	void SetWalking();
	//Check Hp is under 0
	bool IsDead();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
