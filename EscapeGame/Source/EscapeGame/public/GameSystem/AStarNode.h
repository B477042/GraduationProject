// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AstarNode.generated.h"

UENUM(BlueprintType)
 enum class EPathTarget : uint8
{
	
	Key,Gate
};

UCLASS()
class ESCAPEGAME_API AAstarNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstarNode();
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	UFUNCTION()
		void OnActorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
		void OnActorOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	bool operator<(const AAstarNode& lhs);
	//bool operator<(const AAstarNode& lhs, const AAstarNode& rhs);
	bool operator>(const AAstarNode& lhs);
	bool operator==(const AAstarNode& lhs);
	//FCount가 적은 순으로 정렬한다.->기각
	void SortNearNodes();
	

	//	
	UFUNCTION()
		void Activate();
	//
	UFUNCTION()
		void Deactivate();
	//
	UFUNCTION()
		void SetRoad(bool bResult);
	//
	void VisitNode() { bIsVisited = true; }
	void SetToPath() { bIsPath = true; }

	bool IsPath() { return bIsPath; }
	bool IsVisitedNode() { return bIsVisited; }

	void SetPrevNode(AAstarNode* prev) { PrevNode = prev; }

	TWeakObjectPtr<AAstarNode> GetPrevNode() { return PrevNode; }

	//주변 노드들의 이전 노드들을 자신의 노드로한다. 폐기 
	void SetNearNodesPrevAsMe();

	const int GetF() { return Count_F; }
	const int GetH() { return Count_H; }
	const int GetG() { return Count_G; }

	//A* 연산과 관련된 연산 내용들을 초기화 시킨다. 다시 찾기 전에
	void ResetAStarValue();


	//G와 H카운트도 같이 계산된다
	int CalcFCount(const FVector & Start, const FVector & Goal);
	
	UPROPERTY(EditAnywhere, Category = "Astar Data",meta = (AllowPrivateAccess = "true"))
	TArray<TWeakObjectPtr<AAstarNode>>NearNodes;


protected:
	void initComponents();
	int CalcGCount(const FVector& Start);
	int CalcHCount(const FVector& Goal);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* BoxTrigger;
	//


	//
	UPROPERTY(EditAnywhere, Category = "Astar Data",meta = (AllowPrivateAccess = "true"))
		bool bIsPath;
	UPROPERTY(EditAnywhere, Category = "Astar Data", meta = (AllowPrivateAccess = "true"))
		bool bIsVisited;
	UPROPERTY(EditAnywhere, Category = "Astar Data", meta = (AllowPrivateAccess = "true"))
		bool bIsGoalNode;
	UPROPERTY(EditAnywhere, Category = "Astar Data", meta = (AllowPrivateAccess = "true"))
	bool bIsKeyNode;

	UPROPERTY(VisibleAnywhere, Category = "Astar Data", meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<AAstarNode>PrevNode;
	//G+H
	UPROPERTY(VisibleAnywhere, Category = "Astar Data")
	int Count_F;
	//지금까지 비용
	UPROPERTY(VisibleAnywhere, Category = "Astar Data")
	int Count_G;
	//예상비용
	UPROPERTY(VisibleAnywhere, Category = "Astar Data")
	int Count_H;
};

//DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerEnter, AAstarNode*);
//DECLARE_MULTICAST_DELEGATE(FOnPlayerExit);

//경로 업데이트 델리게이트
//static FOnPlayerEnter OnPlayerEnter;
////Finder의 Start노드 초기화
//static FOnPlayerExit OnPlayerExit;