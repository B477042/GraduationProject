// Fill out your copyright notice in the Description page of Project Settings.
/*
	Item Inventory Component.
	Save Item into Array

*/
#pragma once

#include "EscapeGame.h"
#include "ItemActor.h"
#include "Components/ActorComponent.h"
#include "Component_Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemAdded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemUsed);



USTRUCT( meta = (ToolTip = "�κ��丮�� ����Ǵ� �����ۿ� ���� ����"))
struct  FItemDataInfo
{
	GENERATED_BODY()
	public:
	FItemDataInfo() { Item = nullptr; n_item = 0; }
	
	//�������� ����Ѵ�.����� �� 0���ϰ� �Ǹ� �κ��丮���� ������ߵȴ�.
	//item�� ������ 0�� �ȴٸ� false�� �����Ѵ�
	bool UseItem(ACharacter* UserActor)
	{
		//���� üũ��
		if (n_item <= 0)return false;
		//�������� ����մϴ�
		n_item --;
		//����� 0 ���ϰ� �ȴٸ� ��� �� false�� �����մϴ�
		if (n_item <= 0)
		{
			Item->UseMe(UserActor);
			return false;
		}
		Item->UseMe(UserActor);
		return true;
	}
	//�������� ���� ��ȯ�ȴ�
	int GetAmountItems() { return n_item; }
	//���� �߰��ȴ�. ������ 0�̶�� ��ȯ
	void AddItem(int num)
	{
		//EGLOG(Error, TEXT("Add : %d"), num);
		if (num <= 0)return;
		
		n_item +=  num;
		
	}
	TWeakObjectPtr<AItemActor> GetItem() { return Item; }
	void SetItemInfo( AItemActor* Other, int num)
	{
		Item = Other;
		if (num >= 0)n_item = num;
	}

private:
	//�� �������� ����
	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<AItemActor> Item;
	//�� �������� ����
	UPROPERTY(Transient, VisibleAnywhere)
	int n_item;
	

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
		bool UseItem(FName ItemName,ACharacter* UserActor);
	
	
private:
	//FString���� ������ �̸��� �ް� �����ؼ� ����Ѵ�
	UPROPERTY(EditAnywhere, Category = "Items")
		TMap<FName,  FItemDataInfo> Items;
	//
	UPROPERTY(VisibleAnywhere, Category = "Capacity")
		int32 CurrnetCapacity;

};
