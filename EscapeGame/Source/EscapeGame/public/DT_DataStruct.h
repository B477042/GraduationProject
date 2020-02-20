﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "DT_DataStruct.generated.h"

 USTRUCT(BlueprintType)
struct FPlayerTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	//Current Player Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 Level;
	//Current Player Max Hp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 MaxHp;
	//Current Player Default Atk
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 Atk;
	//Need To Level Up amout of Exp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 NextExp;
	//Inventory Slot. Share With Skill slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 Slot;
	void ShowInfo()
	{
		UE_LOG(LogTemp, Error, TEXT("level : %d, maxHp : %d, Atk : %d, NextExp : %d,Slot : %d"),Levl,MaxHp,Atk,NextExp,Slot);
	}
};


USTRUCT(BlueprintType)
struct FEnemyTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:

	//Sort of Enemy Stat Type. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 Type;
	//Enemy's Max Hp
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 MaxHp;
	//Enemy's Default Atk
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 Atk;
	//Enemy's Drop Point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 DropExp;

};

UCLASS()
class ESCAPEGAME_API ADT_DataStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADT_DataStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
