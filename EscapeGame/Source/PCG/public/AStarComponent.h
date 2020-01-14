// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PCG.h"
#include "Components/ActorComponent.h"
#include "AStarComponent.generated.h"


/*
AStar 알고리즘으로 만든 컴포넌트

어떻게 쓸지는 정의하지 않는다

*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PCG_API UAStarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAStarComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:


};
