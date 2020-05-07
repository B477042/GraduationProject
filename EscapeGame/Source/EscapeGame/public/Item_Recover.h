// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ItemActor.h"
#include "Item_Recover.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AItem_Recover : public AItemActor
{
	GENERATED_BODY()

public:

	AItem_Recover();
	virtual void BePickedUp(ACharacter* OtherActor)override;

protected:
	virtual void useMe()override;

private:
	//if true, this actor hide from world
	UPROPERTY(EditAnywhere)
	bool bIsActivate;    
	UPROPERTY(VisibleAnywhere)
	uint32 amount_Recover;

};
