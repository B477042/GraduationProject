// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "AstarNode.h"
#include "Containers/Queue.h"
//#include "Containers/pri"
//#include "Containers/"
#include "GameFramework/Actor.h"
#include "AstarFinder.generated.h"




UCLASS()
class ESCAPEGAME_API AAStarFinder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarFinder();
	//static AAStarFinder* GetInstance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PostInitializeComponents()override;
public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	void  PathFind( AAstarNode* Start, EPathTarget Mode);


	//Activate PathNodes
	void ShowPath(EPathTarget Mode);
	void StartPathFinder(AAstarNode* Other, EPathTarget Mode);
	void SetGoalPoint(AAstarNode * Other);
	void SetKeyPoint(AAstarNode*Other);
	void ResetResult();
	
	//Add Node To Tarray
	void AddNode(AAstarNode* Other);
	void ClearNodes();
private:
	
	void GoalFind(AAstarNode* Start, AAstarNode* Goal);
	void KeyFind(AAstarNode* Start, AAstarNode* Goal);

private:
	
	//방문해야될 노드
	//UPROPERTY(Transient)
	TQueue<TWeakObjectPtr<AAstarNode>>ToVisiteNodes;

	//Goal Node in map
	UPROPERTY(Transient, EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<AAstarNode> GoalNode;

	//CardKey Node
	TWeakObjectPtr<AAstarNode>KeyNode;
	
	UPROPERTY(Transient, meta = (DisplayName = "Nodes"))
		TArray< TWeakObjectPtr<AAstarNode>>AllNodes;
	
	/*UPROPERTY(Transient, meta = (DisplayName = "Nodes"))
		TArray<AAstarNode*>AllNodes;*/
	
};
