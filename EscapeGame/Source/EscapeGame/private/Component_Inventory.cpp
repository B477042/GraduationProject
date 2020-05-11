// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Inventory.h"
#include"ItemActor.h"

// Sets default values for this component's properties
UComponent_Inventory::UComponent_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	//Tag = "Item";
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

	//EGLOG(Warning, TEXT("input Item Tag Name : %s"), *AddItem->GetTag().ToString());
	//만약 이 아이템이 이미 가지고 있는 것이라면
	if (Items.Contains(AddItem->GetTag()))
	{
		 Items[AddItem->GetTag()].AddItem(Amount);

		//EGLOG(Warning, TEXT("Current Amount : %d"), tempData.GetAmountItems());

		return true;
	}

	else
	{
		
		FItemDataInfo tempData ;
		tempData.SetItemInfo(AddItem, Amount);
		//EGLOG(Warning, TEXT("Item Tag Name : %s"), *tempData.GetItem()->GetTag().ToString());
		Items.Add(tempData.GetItem()->GetTag(), tempData);
		//EGLOG(Warning, TEXT("Current Amount : %d"), tempData.GetAmountItems());
		return true;
	}
	return false;


}
//아이템을 사용합니다. 성공적으로 사용했다면 사용자의 위치에 이펙트를 뿌려줍니다.
bool UComponent_Inventory::UseItem(FName ItemName, ACharacter* UserActor)
{
	EGLOG(Warning, TEXT("Pressed"));
	if (!Items.Contains(ItemName)) { EGLOG(Warning, TEXT("Not contain Such Item")); return false; }
	//아이템을 사용합니다.
	//아이템의 갯수가 0 이하가 되면 이 아이템은 inventory에서 사라져야 됩니다.
	if (!Items[ItemName].UseItem(UserActor))
	{
		Items.Remove(ItemName);
	}
	return true;
}


