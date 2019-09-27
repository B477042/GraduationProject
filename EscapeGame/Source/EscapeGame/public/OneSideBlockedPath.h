// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "OneSideBlockedPath.generated.h"

UCLASS()
class ESCAPEGAME_API AOneSideBlockedPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOneSideBlockedPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Plate;//�ٴ�
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* MiddleWall;//��� ��
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Ceiling;//õ��
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LampMesh;//õ�� ����

	UPROPERTY(VisibleAnywhere, Category = SpotLight)
		USpotLightComponent* LampLight;


};
