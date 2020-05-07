// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Recover.h"

AItem_Recover::AItem_Recover()
{
	amount_Recover = 40;
}

void AItem_Recover::BePickedUp(ACharacter * OtherActor)
{
	Super::BePickedUp(OtherActor);


}

void AItem_Recover::useMe()
{

}
