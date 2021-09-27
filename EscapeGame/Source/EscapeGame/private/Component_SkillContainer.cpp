// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_SkillContainer.h"

// Sets default values for this component's properties
UComponent_SkillContainer::UComponent_SkillContainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	// ...
}


// Called when the game starts
void UComponent_SkillContainer::BeginPlay()
{
	Super::BeginPlay();


}

void UComponent_SkillContainer::BeginDestroy()
{
	Super::BeginDestroy();
	/*for (auto it : SkillObjects)
	{
		it->Destroy();
	}
	SkillObjects.Empty();
*/
}


// Called every frame
void UComponent_SkillContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UComponent_SkillContainer::AddSkillObj(TWeakObjectPtr<ASkillActor> Input)
{
	if (!Input.IsValid())
	{
		EGLOG(Error, TEXT("input actor is null"));
		return;
	}
	
	SkillObjects[Index] = Input.Get();
	SkillObjects[Index]->SetOwner(GetOwner());

	revolve();

}

//슬롯에 있는 다음 엑터를 준비시킨다
void UComponent_SkillContainer::revolve()
{
	
	//EGLOG(Error, TEXT("Rolling"));
	if(!CurrentIndex.IsValid())
		CurrentIndex = SkillObjects[Index];

	Index++;

	if (Index >= ArraySize)
		Index = 0;

	if(SkillObjects[ArraySize-1]!=nullptr)
		CurrentIndex = SkillObjects[Index];
	
}

void UComponent_SkillContainer::clear()
{
	SkillObjects.Empty();

}

