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



USTRUCT(BlueprintType, meta = (ToolTip = "인벤토리에 저장되는 아이템에 대한 정보"))
struct  FItemDataInfo
{
	GENERATED_BODY()
	public:
	FItemDataInfo() { Item = nullptr; n_item = 0; }
	//아이템을 사용한다.사용한 후 0이하가 되면 0으로 고정된다
	void UseItem(int32 num)
	{
		if (n_item <= 0)return;
		n_item -= num;
		if (n_item < 0)n_item = 0;

	}
	//아이템의 양이 반환된다
	int32 GetAmountItems() { return n_item; }
	//양이 추가된다. 음수나 0이라면 반환
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
	//이 아이템의 종류
	UPROPERTY(VisibleAnywhere)
	class AItemActor* Item;
	//이 아이템의 갯수
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
	//FString으로 아이템 이름을 받고 리턴해서 사용한다
	UPROPERTY(VisibleAnywhere, Category = "Items")
		TMap<FString,  FItemDataInfo> Items;
	//
	UPROPERTY(VisibleAnywhere, Category = "Capacity")
		int32 CurrnetCapacity;

};
