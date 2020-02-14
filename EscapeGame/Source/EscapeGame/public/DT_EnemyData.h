// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DT_EnemyData.generated.h"

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
class ESCAPEGAME_API ADT_EnemyData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADT_EnemyData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
