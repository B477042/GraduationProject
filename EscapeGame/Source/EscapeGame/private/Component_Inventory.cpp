// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Inventory.h"

#include"ItemActor.h"

// Sets default values for this component's properties
UComponent_Inventory::UComponent_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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
	FName ItemTag = AddItem->GetTag();
	
	if (Items.Contains(ItemTag))
	{
		 Items[ItemTag].AddItem(Amount);
		
		 OnItemUpdated.Execute(ItemTag ,Items[ItemTag].GetAmountItems());
		return true;
	}

	//처음 생성할 때
	else
	{
		FItemDataInfo tempData ;
		tempData.SetItemInfo(AddItem, Amount);
		Items.Add(tempData.GetItem()->GetTag(), tempData);
		OnItemUpdated.Execute(ItemTag, Amount);
		return true;
	}
	return false;
}
//아이템을 사용합니다. 성공적으로 사용했다면 사용자의 위치에 이펙트를 뿌려줍니다.
bool UComponent_Inventory::UseItem(FName ItemName, ACharacter* UserActor)
{
	if (!Items.Contains(ItemName)) { EGLOG(Warning, TEXT("There is no such item")); return false; }
	//아이템을 사용합니다.
	//아이템의 갯수가 0 이하가 되면 이 아이템은 inventory에서 사라져야 됩니다.
	if (!Items[ItemName].UseItem(UserActor))
	{
		OnItemUpdated.Execute(ItemName, 0);
		Items.Remove(ItemName);
	}
	else
	{
		int Amount = Items[ItemName].GetAmountItems();
		OnItemUpdated.Execute(ItemName, Amount);
	}
	
	
	return true;
}

bool UComponent_Inventory::HasItem(FName ItemName)
{
	return	Items.Contains(ItemName);
	//return false;
}

int UComponent_Inventory::GetAmountItem(FName Name)
{	
	//없으면 음수로 보낸다
	if (!Items.Contains(Name))return -1;

	return Items[Name].GetAmountItems();
}

bool UComponent_Inventory::LoadGameData(AItemActor * newItem, int Amount)
{
	//만약 실패하면 false로 바꿔서 리턴
	bool bResult = true;
	/*
		1. 받아온 Item Actor의 콜린전 반응을 끄고 게임에서 숨긴다
		2. 이 Item Actor의 Tag로 인벤토리에 넣어준다.
	*/
	newItem->SetItemDisable();
	bResult = AddItem(newItem, Amount);


	return bResult;
}
