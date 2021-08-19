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

	void SetPrevNode(AAstarNode* prev) { PrevNode = prev; }

	TWeakObjectPtr<AAstarNode> GetPrevNode() { return PrevNode; }

	//�ֺ� ������ ���� ������ �ڽ��� �����Ѵ�. ��� 
	void SetNearNodesPrevAsMe();

	const int GetF() { return Count_F; }
	const int GetH() { return Count_H; }
	const int GetG() { return Count_G; }

	//A* ����� ���õ� ���� ������� �ʱ�ȭ ��Ų��. �ٽ� ã�� ����
	void ResetAStarValue();


	//G�� Hī��Ʈ�� ���� ���ȴ�
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
	//���ݱ��� ���
	UPROPERTY(VisibleAnywhere, Category = "Astar Data")
	int Count_G;
	//������
	UPROPERTY(VisibleAnywhere, Category = "Astar Data")
	int Count_H;
};

//DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerEnter, AAstarNode*);
//DECLARE_MULTICAST_DELEGATE(FOnPlayerExit);

//��� ������Ʈ ��������Ʈ
//static FOnPlayerEnter OnPlayerEnter;
////Finder�� Start��� �ʱ�ȭ
//static FOnPlayerExit OnPlayerExit;