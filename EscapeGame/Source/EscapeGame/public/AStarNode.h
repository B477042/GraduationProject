// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include  "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "AStarNode.generated.h"

/*
	��� ��� : ���忡 ��ġ�ؼ� ���� �̾� ���δ�

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
	//�Դ� ���
	int Count_G;
	//������
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
	//ȭ�鿡 ����ش�.
	UFUNCTION()
	void Activate();
	//ȭ�鿡�� �����ش� 
	UFUNCTION()
	void Deactivate();
	//��� �����Ѵ�.
	UFUNCTION()
	void SetRoad(bool bResult);
	//��带 �湮�� ���� �ٲ۴�. 
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
	//�پ� �ִ� ����. �����Ϳ��� �����ؼ� ���̰ų� Ž���ؼ� ���δ�. 
	UPROPERTY(EditAnywhere,  meta = (AllowPrivateAccess = "true"))
	TArray<TWeakObjectPtr<AAStarNode>>NearNodes;
	
	//��η� ��������//SetRoad������ true�� ���� ��
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bIsPath;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bIsVisited;
	UPROPERTY(VisibleAnywhere)
	FAstarCount AstarCount;
};
