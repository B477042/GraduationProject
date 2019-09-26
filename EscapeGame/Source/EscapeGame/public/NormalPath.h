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
		UStaticMeshComponent* plate;//바닥
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* leftSideWall;//좌측벽
		UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* rightSideWall;//우측벽
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* ceiling;//천장
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* lampMesh;//천장 전등

	UPROPERTY(VisibleAnywhere, Category = SpotLight)
		USpotLightComponent* lampLight;

};
