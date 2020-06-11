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

//싱크는 BP에서 맞춘다
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemChanged);




USTRUCT(BlueprintType, meta = (ToolTip = "인벤토리에 저장되는 아이템에 대한 정보"))
struct  FItemDataInfo
{
	GENERATED_BODY()
	public:
	FItemDataInfo() { Item = nullptr; n_item = 0; }

	UPROPERTY(BlueprintAssignable)
	FOnItemChanged OnItemChanged;
	//아이템을 사용한다.사용한 후 0이하가 되면 인벤토리에서 사라져야된다.
	//item의 갯수가 0이 된다면 false를 리턴한다
	bool UseItem(ACharacter* UserActor)
	{
		//에러 체크용
		if (n_item <= 0)return false;
		//아이템을 사용합니다
		n_item --;
		OnItemChanged.Broadcast();

		//사용후 0 이하가 된다면 사용 후 false를 리턴합니다
		if (n_item <= 0)
		{
			Item->UseMe(UserActor);
			
			return false;
		}
		Item->UseMe(UserActor);
		return true;
	}
	//아이템의 양이 반환된다

	int GetAmountItems() { return n_item; }
	//양이 추가된다. 음수나 0이라면 반환
	void AddItem(int num)
	{
		//EGLOG(Error, TEXT("Add : %d"), num);
		if (num <= 0)return;

		OnItemChanged.Broadcast();

		n_item +=  num;
		
	}
	TWeakObjectPtr<AItemActor> GetItem() { return Item; }
	void SetItemInfo( AItemActor* Other, int num)
	{
		Item = Other;
		if (num >= 0)n_item = num;
	}

	


private:
	//이 아이템의 종류
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<AItemActor> Item;
	//이 아이템의 갯수
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
	// Called every frame
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
	/*UFUNCTION()
		FOnItemChanged GetItemChangeDelegate(FName ItemName);*/

private:
	//FName으로 아이템 이름을 받고 리턴해서 사용한다
	UPROPERTY(EditAnywhere, Category = "Items")
		TMap<FName,  FItemDataInfo> Items;
	//
	/*UPROPERTY(VisibleAnywhere, Category = "Capacity")
		int32 CurrnetCapacity;*/

};
