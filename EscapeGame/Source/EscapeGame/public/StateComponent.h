// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

/*

	Anim을 설정하는데 도움을 줄 수 있는 컴포넌트
	상태를 정의한다.
	입력을 제한하거나 풀어주거나
	현재 엑션 상태를 바꿔준다
	Stat 컴포넌트에 있던 기능들을 옮겨온다
	

	2020 05 14 Stat Comp랑 꼬인 코드를 풀어준다

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
