// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "AStarNode.h"
#include "Containers/Queue.h"
//#include "Containers/pri"
//#include "Containers/"
#include "GameFramework/Actor.h"
#include "AstarFinder.generated.h"

UCLASS()
class ESCAPEGAME_API AAstarFinder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstarFinder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void  AStar( AAStarNode* Start,  AAStarNode* Goal);
	//Activate PathNodes
	void ShowPath();



private:
	
	//방문해야될 노드
	TQueue<TWeakObjectPtr<AAStarNode>>ToVisiteNodes;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<AAStarNode> GoalNode;
	

};
