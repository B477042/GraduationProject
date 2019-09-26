// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"

#include "NormalPath.generated.h"

UCLASS()
class ESCAPEGAME_API ANormalPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANormalPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* plate;//�ٴ�
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* leftSideWall;//������
		UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* rightSideWall;//������
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* ceiling;//õ��
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* lampMesh;//õ�� ����

	UPROPERTY(VisibleAnywhere, Category = SpotLight)
		USpotLightComponent* lampLight;

};
