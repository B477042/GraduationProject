// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Inventory.h"
#include"ItemActor.h"

// Sets default values for this component's properties
UComponent_Inventory::UComponent_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	Tag = "Item";
	// ...
}


// Called when the game starts
void UComponent_Inventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComponent_Inventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



/*

	입력 받은 아이템을 인벤토리에 추가합니다
	입력 받은 아이템의 테그를 itmes에 테그를 검색하고

	있을경우) 갯수를 늘려고
	없을경우) 새로 추가해줍니다
*/
bool UComponent_Inventory::AddItem(AItemActor * AddItem, int Amount)
{
	if (!AddItem)return false;
	//만약 이 아이템이 이미 가지고 있는 것이라면
	if (Items.Contains(AddItem->GetTag()))
	{
		auto tempData = Items[AddItem->GetTag()];
		tempData->AddItem(Amount);

		return true;
	}

	else
	{
		auto tempData = new FItemDataInfo();
		tempData->SetItemInfo(AddItem, Amount);
		Items.Add(tempData->GetItem()->GetTag(), tempData);
		return true;
	}
	return false;
}

bool UComponent_Inventory::UseItem(AItemActor * UsedItem)
{

	return false;
}

