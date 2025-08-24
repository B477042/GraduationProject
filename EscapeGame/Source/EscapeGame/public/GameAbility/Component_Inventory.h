// Fill out your copyright notice in the Description page of Project Settings.
/*
	Item Inventory Component.
	Save Item into Array

*/
#pragma once


#include "Components/ActorComponent.h"
#include "Component_Inventory.generated.h"


class AItemActor;
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemChanged);
DECLARE_DELEGATE_TwoParams(FOnItemUpdated, FName, int);



USTRUCT(BlueprintType, meta = (ToolTip = "�κ��丮�� ����Ǵ� �����ۿ� ���� ����"))
struct  FItemDataInfo
{
	GENERATED_BODY()
	public:
	FItemDataInfo() { Item = nullptr; n_item = 0; }


	//If the number of items becomes zero after using them,
	// remove the item from the inventory and return false.
	bool UseItem(ACharacter* UserActor);

	//return number of item
	int GetAmountItems() { return n_item; }

	//Increase the amount by num
	void AddItem(int num);
	

	void SetItemInfo(AItemActor* Other, int num);

	TWeakObjectPtr<AItemActor> GetItem();	
private:
	//Sort of this item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<AItemActor> Item;
	
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
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
	// Called every frame. NOT USED
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Add Item Actor To Inventory
	UFUNCTION()
		bool AddItem(class AItemActor* AddItem, int Amount);
	//Use Item From Inventory
	UFUNCTION()
		bool UseItem(FName ItemName,ACharacter* UserActor);
	UFUNCTION()
	bool HasItem(FName ItemName);

	UFUNCTION(BlueprintCallable, Category = "Custom")
		int GetAmountItem(FName Name);


	bool LoadGameData(AItemActor* newItem, int Amount);
	
	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Delegate")
	FOnItemUpdated OnItemUpdated;
	
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Items")
		TMap<FName,  FItemDataInfo> Items;
	
	

};
