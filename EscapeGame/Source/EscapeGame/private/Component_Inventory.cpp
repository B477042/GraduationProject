// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/Component_Inventory.h"

#include "EscapeGame.h"
#include "Actor/Item/ItemActor.h"

bool FItemDataInfo::UseItem(ACharacter* UserActor)
{
	if (n_item <= 0)return false;
	//Use Item
	n_item --;
	//OnItemChanged.Broadcast();

	//If the number is less than zero after use,retun false.
	if (n_item <= 0)
	{
		Item->UseMe(UserActor);
			
		return false;
	}
	Item->UseMe(UserActor);
	return true;
}

void FItemDataInfo::AddItem(int num)
{
	if (num <= 0)return;

	//OnItemChanged.Broadcast();

	n_item +=  num;
		
}

void FItemDataInfo::SetItemInfo(AItemActor* Other, int num)
{
	Item = Other;
	if (num >= 0)n_item = num;
}

TWeakObjectPtr<AItemActor> FItemDataInfo::GetItem()
{
	return Item;
}

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

	�Է� ���� �������� �κ��丮�� �߰��մϴ�
	�Է� ���� �������� �ױ׸� itmes�� �ױ׸� �˻��ϰ�

	�������) ������ �÷���
	�������) ���� �߰����ݴϴ�
*/
bool UComponent_Inventory::AddItem(AItemActor * AddItem, int Amount)
{
	if (!AddItem)return false;
	//���� �� �������� �̹� ������ �ִ� ���̶��
	FName ItemTag = AddItem->GetTag();
	
	if (Items.Contains(ItemTag))
	{
		 Items[ItemTag].AddItem(Amount);
		
		 OnItemUpdated.Execute(ItemTag ,Items[ItemTag].GetAmountItems());
		return true;
	}

	//ó�� ������ ��
	
	FItemDataInfo tempData ;
	tempData.SetItemInfo(AddItem, Amount);
	Items.Add(tempData.GetItem()->GetTag(), tempData);
	OnItemUpdated.Execute(ItemTag, Amount);
	return true;
	
}
//�������� ����մϴ�. ���������� ����ߴٸ� ������� ��ġ�� ����Ʈ�� �ѷ��ݴϴ�.
bool UComponent_Inventory::UseItem(FName ItemName, ACharacter* UserActor)
{
	if (!Items.Contains(ItemName)) { EGLOG(Warning, TEXT("There is no such item")); return false; }
	//�������� ����մϴ�.
	//�������� ������ 0 ���ϰ� �Ǹ� �� �������� inventory���� ������� �˴ϴ�.
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
	//������ ������ ������
	if (!Items.Contains(Name))return -1;

	return Items[Name].GetAmountItems();
}

bool UComponent_Inventory::LoadGameData(AItemActor * newItem, int Amount)
{
	//���� �����ϸ� false�� �ٲ㼭 ����
	bool bResult = true;
	/*
		1. �޾ƿ� Item Actor�� �ݸ��� ������ ���� ���ӿ��� �����
		2. �� Item Actor�� Tag�� �κ��丮�� �־��ش�.
	*/
	newItem->SetItemDisable();
	bResult = AddItem(newItem, Amount);


	return bResult;
}
