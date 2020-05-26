// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AStarNode.h"
#include "GameFramework/Actor.h"
#include "AStarFinder.generated.h"

UCLASS()
class ESCAPEGAME_API AAStarFinder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarFinder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool FindPath(const FVector& Start, const FVector& Goal);


private:
	//방문을 해야될 노드
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TQueue<AAStarNode>Que_ToVisit;
	
	//경로
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TList<AAStarNode>Que_Path;
};
