// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_SkillContainer.h"

// Sets default values for this component's properties
UComponent_SkillContainer::UComponent_SkillContainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UComponent_SkillContainer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComponent_SkillContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

template <typename T>
void UComponent_SkillContainer::AddSkillObj(T * Input, int num)
{
	auto typeTest = Cast<AActor>(Input);

	if (!typeTest)
	{
		EGLOG(Warning, TEXT("typeTest Failed"));
		return;
	}

	for (int i = 0; i < num; i++)
	{
		SkillObjects.Emplace(GetWorld()->SpawnActor<T>());
		
	}

	
	Index = 0;
	CurrentIndex = SkillObjects[Index];
}

void UComponent_SkillContainer::revolve()
{
	
	int lastNum = 0;
	TWeakObjectPtr<AActor> tempActor;
	if (!SkillObjects.FindLast(tempActor, lastNum))return;

	if (Index+1 >= lastNum)
		Index = 0;
	
	
	Index++;
	CurrentIndex = SkillObjects[Index];
	
}

