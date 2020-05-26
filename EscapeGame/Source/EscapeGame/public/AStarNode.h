// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include  "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "AStarNode.generated.h"

/*
	사용 방법 : 월드에 배치해서 직접 이어 붙인다

*/

USTRUCT()
struct FAstarCount
{
	GENERATED_BODY()
public:
	FAstarCount(){
		Count_F = 0;
		Count_G = 0;
		Count_H = 0;
	}

	//G+H
	int Count_F;
	//왔던 비용
	int Count_G;
	//예상비용
	int Count_H;

};

UCLASS()
class ESCAPEGAME_API AAStarNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStarNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
	void OnActorOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//화면에 띄워준다.
	UFUNCTION()
	void Activate();
	//화면에서 지워준다 
	UFUNCTION()
	void Deactivate();
	//길로 설정한다.
	UFUNCTION()
	void SetRoad(bool bResult);
	//노드를 방문한 노드로 바꾼다. 
	void VisitNode() { bIsVisited = true; }

	bool IsPath() { return bIsPath; }

	bool IsVisitedNode() { return bIsVisited; }

	FAstarCount& GetAstarCount() { return AstarCount; }
protected:
	void initComponents();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxTrigger;
	//붙어 있는 노드들. 에디터에서 설정해서 붙이거나 탐지해서 붙인다. 
	UPROPERTY(EditAnywhere,  meta = (AllowPrivateAccess = "true"))
	TArray<TWeakObjectPtr<AAStarNode>>NearNodes;
	
	//경로로 뽑혔는지//SetRoad에서만 true로 만들 것
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bIsPath;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bIsVisited;
	UPROPERTY(VisibleAnywhere)
	FAstarCount AstarCount;
};
