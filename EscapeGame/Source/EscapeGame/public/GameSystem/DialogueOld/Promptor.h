// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Promptor.generated.h"

/*
다이얼로그 지정용

*/

UCLASS()
class ESCAPEGAME_API APromptor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APromptor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
		FName NextStage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
		int n_Act;



};
