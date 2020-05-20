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

	�Է� ���� �������� �κ��丮�� �߰��մϴ�
	�Է� ���� �������� �ױ׸� itmes�� �ױ׸� �˻��ϰ�

	�������) ������ �÷���
	�������) ���� �߰����ݴϴ�
*/
bool UComponent_Inventory::AddItem(AItemActor * AddItem, int Amount)
{


	if (!AddItem)return false;

	//EGLOG(Warning, TEXT("input Item Tag Name : %s"), *AddItem->GetTag().ToString());
	//���� �� �������� �̹� ������ �ִ� ���̶��
	if (Items.Contains(AddItem->GetTag()))
	{
		 Items[AddItem->GetTag()].AddItem(Amount);

		//EGLOG(Warning, TEXT("Current Amount : %d"), tempData.GetAmountItems());

		return true;
	}

	//ó�� ������ ��
	else
	{
		
		FItemDataInfo tempData ;
		tempData.SetItemInfo(AddItem, Amount);
		//EGLOG(Warning, TEXT("Item Tag Name : %s"), *tempData.GetItem()->GetTag().ToString());
		Items.Add(tempData.GetItem()->GetTag(), tempData);
		
		////widget���� inventory�� ȣ���� �� �ְ� �����Ѵ�
		////������ִٸ� �׸��д�
		//auto tempChara = Cast<ACharacter>(GetOwner());
		//if (!tempChara)return true;
		//auto tempCon = Cast<AEGPlayerController>(tempChara->Controller);
		//if (!tempCon)return true;
		//tempCon->GetHUDWidget()->BindCharacterInven(this);

		//EGLOG(Warning, TEXT("Current Amount : %d"), tempData.GetAmountItems());
		return true;
	}
	return false;


}
//�������� ����մϴ�. ���������� ����ߴٸ� ������� ��ġ�� ����Ʈ�� �ѷ��ݴϴ�.
bool UComponent_Inventory::UseItem(FName ItemName, ACharacter* UserActor)
{
	EGLOG(Warning, TEXT("Pressed"));
	if (!Items.Contains(ItemName)) { EGLOG(Warning, TEXT("Not contain Such Item")); return false; }
	//�������� ����մϴ�.
	//�������� ������ 0 ���ϰ� �Ǹ� �� �������� inventory���� ������� �˴ϴ�.
	if (!Items[ItemName].UseItem(UserActor))
	{
		Items.Remove(ItemName);
	}
	return true;
}

int UComponent_Inventory::GetAmountItem(FName Name)
{	
	//������ ������ ������
	if (!Items.Contains(Name))return -1;

	return Items[Name].GetAmountItems();
}

////nullptr üũ �� �ؾߵ�. �������� ������ �ִ� ��������Ʋ ȣ���ؼ� ������ ��
//FOnItemChanged UComponent_Inventory::GetItemChangeDelegate(FName ItemName)
//{
//
//	if(!Items.Contains(ItemName))
//	return ;
//
//	return Items[ItemName].OnItemChanged;
//}


