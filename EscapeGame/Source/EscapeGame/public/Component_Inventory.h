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
		bool AddItem(class AItemActor* AddItem);
	//Use Item From Inventory
	UFUNCTION()
		bool UseItem(class AItemActor* UsedItem);

private:

	UPROPERTY(VisibleAnywhere, Category = "Items")
		TArray<class AItemActor* >Items;

};
