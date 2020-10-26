// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "DT_GameData.generated.h"



UCLASS()
class ESCAPEGAME_API ADT_GameData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADT_GameData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
