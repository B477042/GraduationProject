// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DT_PlayerData.generated.h"

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

};

UCLASS()
class ESCAPEGAME_API ADT_PlayerData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADT_PlayerData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
