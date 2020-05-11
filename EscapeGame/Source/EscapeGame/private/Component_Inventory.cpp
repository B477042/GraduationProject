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

	�Է� ���� �������� �κ��丮�� �߰��մϴ�
	�Է� ���� �������� �ױ׸� itmes�� �ױ׸� �˻��ϰ�

	�������) ������ �÷���
	�������) ���� �߰����ݴϴ�
*/
bool UComponent_Inventory::AddItem(AItemActor * AddItem, int Amount)
{
	if (!AddItem)return false;
	//���� �� �������� �̹� ������ �ִ� ���̶��
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

