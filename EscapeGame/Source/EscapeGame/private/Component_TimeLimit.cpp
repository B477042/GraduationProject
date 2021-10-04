// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_TimeLimit.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UComponent_TimeLimit::UComponent_TimeLimit()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	RemainTime = 60;
	// ...
}


void UComponent_TimeLimit::TimeExtend(const float& AddTime)
{
	RemainTime += AddTime;
	
}

float UComponent_TimeLimit::GetCurrentRemainTime() const
{
	return RemainTime;
}

void UComponent_TimeLimit::LoadTime(float NewTime)
{
	RemainTime = NewTime;
}

void UComponent_TimeLimit::SetTimerActive(bool bResult)
{
	SetComponentTickEnabled(bResult);
}

void UComponent_TimeLimit::BeginDestroy()
{
	Super::BeginDestroy();

	if (OnTimeOver.IsBound())
	{
		OnTimeOver.Unbind();
	}
}

// Called when the game starts
void UComponent_TimeLimit::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UComponent_TimeLimit::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	auto Character = Cast<ACharacter>(GetOwner());
	
	float PlayedTime = DeltaTime;
	RemainTime -= PlayedTime;



	if (RemainTime <= 0)
	{
		RemainTime = 0;
		if (OnTimeOver.IsBound())
		{
			OnTimeOver.Execute();

		}

		//Stop Tick
		SetComponentTickEnabled(false);

	}

}

