// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "AstarNode.h"
#include "Containers/Queue.h"
//#include "Containers/pri"
//#include "Containers/"
#include "UObject/NoExportTypes.h"
#include "AstarFinder.generated.h"




UCLASS()
class ESCAPEGAME_API UAstarFinder : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UAstarFinder();
	static UAstarFinder* GetInstance();

protected:
	// Called when the game starts or when spawned
	/*virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;*/
public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	void  AStar( AAstarNode* Start,  AAstarNode* Goal);
	//Activate PathNodes
	void ShowPath();
	void SetStartPoint(AAstarNode* Other);
	void SetGoalPoint(AAstarNode * Other);
	void ResetResult();
	
	//Add Node To Tarray
	void AddNode(AAstarNode* Other);
	void ClearNodes();
private:
	


private:
	
	//방문해야될 노드
	//UPROPERTY(Transient)
	TQueue<TWeakObjectPtr<AAstarNode>>ToVisiteNodes;

	//Goal Node in map
	UPROPERTY(Transient, EditInstanceOnly, meta = (AllowPrivateAccess = "true", DisplayName = "Nodes"))
	TWeakObjectPtr<AAstarNode> GoalNode;
	
	UPROPERTY(Transient, meta = (DisplayName = "Nodes"))
		TArray< TWeakObjectPtr<AAstarNode>>AllNodes;
	
	
};
