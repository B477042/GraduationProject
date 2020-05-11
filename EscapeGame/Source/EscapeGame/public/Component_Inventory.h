// Fill out your copyright notice in the Description page of Project Settings.
/*
	Item Inventory Component.
	Save Item into Array

*/
#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "Component_Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemAdded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemUsed);



USTRUCT(BlueprintType, meta = (ToolTip = "�κ��丮�� ����Ǵ� �����ۿ� ���� ����"))
struct  FItemDataInfo
{
	GENERATED_BODY()
	public:
	FItemDataInfo() { Item = nullptr; n_item = 0; }
	//�������� ����Ѵ�.����� �� 0���ϰ� �Ǹ� 0���� �����ȴ�
	void UseItem(int32 num)
	{
		if (n_item <= 0)return;
		n_item -= num;
		if (n_item < 0)n_item = 0;

	}
	//�������� ���� ��ȯ�ȴ�
	int32 GetAmountItems() { return n_item; }
	//���� �߰��ȴ�. ������ 0�̶�� ��ȯ
	void AddItem(int32 num)
	{
		if (num <= 0)return;
		n_item += num;
	}
	class AItemActor* GetItem() { return Item; }
	void SetItemInfo(class AItemActor* Other, int32 num)
	{
		Item = Other;
		if (num >= 0)n_item = num;
	}

private:
	//�� �������� ����
	UPROPERTY(VisibleAnywhere)
	class AItemActor* Item;
	//�� �������� ����
	UPROPERTY(VisibleAnywhere)
	int32 n_item;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UComponent_Inventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Inventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Add Item Actor To Inventory
	UFUNCTION()
		bool AddItem(class AItemActor* AddItem, int Amount);
	//Use Item From Inventory
	UFUNCTION()
		bool UseItem(class AItemActor* UsedItem);
	
	
private:
	//FString���� ������ �̸��� �ް� �����ؼ� ����Ѵ�
	UPROPERTY(VisibleAnywhere, Category = "Items")
		TMap<FString,  FItemDataInfo> Items;
	//
	UPROPERTY(VisibleAnywhere, Category = "Capacity")
		int32 CurrnetCapacity;

};
