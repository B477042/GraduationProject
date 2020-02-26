// Fill out your copyright notice in the Description page of Project Settings.

/*
	PCG�� ����� �⺻���� Ÿ��. 
	�� Ÿ���� �⺻���� ��ο� ����� ���������
	�� Ÿ���� ����� �����Ѵ�.

	�׽�Ʈ ������ Mesh�� �ٿ��ش�

*/

#pragma once

#include "PCG.h"
#include "GameFramework/Actor.h"

#include "Tiles.generated.h"

UCLASS()
class PCG_API ATiles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATiles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector GetTailSize();
	v
private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Mesh;
	//Ÿ���� ��ü ũ��μ� �����ϴµ� ����ϰ� �� ��
	UPROPERTY(EditAnywhere, Category = "Box", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* BoxCollision;
};
