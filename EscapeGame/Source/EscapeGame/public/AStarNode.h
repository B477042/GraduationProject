// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "AStarNode.generated.h"

UCLASS()
class ESCAPEGAME_API AAStarNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarNode();
	virtual void BeginPlay()override;
	virtual void PostInitializeComponents()override;
	UFUNCTION()
		void OnActorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
		void OnActorOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool operator<(const AAStarNode& lhs);
	//bool operator<(const AAStarNode& lhs, const AAStarNode& rhs);
	bool operator>(const AAStarNode& lhs);
	bool operator==(const AAStarNode& lhs);
	//FCount�� ���� ������ �����Ѵ�.->�Ⱒ
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

	void SetPrevNode(AAStarNode* prev) { PrevNode = prev; }

	TWeakObjectPtr<AAStarNode> GetPrevNode() { return PrevNode; }

	//�ֺ� ������ ���� ������ �ڽ��� �����Ѵ�. 
	void SetNearNodesPrevAsMe();

	 int GetF() { return Count_F; }
	const int GetH() { return Count_H; }
	const int GetG() { return Count_G; }

	//A* ����� ���õ� ���� ������� �ʱ�ȭ ��Ų��. �ٽ� ã�� ����
	void ResetAStarValue();


	//G�� Hī��Ʈ�� ���� ���ȴ�
	int CalcFCount(const FVector & Start, const FVector & Goal);
	
	UPROPERTY(EditAnywhere, Category = "Astar Data",meta = (AllowPrivateAccess = "true"))
	TArray<TWeakObjectPtr<AAStarNode>>NearNodes;


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

	UPROPERTY(VisibleAnywhere, Category = "Astar Data", meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<AAStarNode>PrevNode;
	//G+H
	UPROPERTY(VisibleAnywhere, Category = "Astar Data")
	int Count_F;
	//���ݱ��� ���
	UPROPERTY(VisibleAnywhere, Category = "Astar Data")
	int Count_G;
	//������
	UPROPERTY(VisibleAnywhere, Category = "Astar Data")
	int Count_H;
};
