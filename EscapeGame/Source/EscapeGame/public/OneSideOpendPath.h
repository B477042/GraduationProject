// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseStruct.h"
#include "OneSideOpendPath.generated.h"

UCLASS()
class ESCAPEGAME_API AOneSideOpendPath : public ABaseStruct
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOneSideOpendPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Plate;//바닥
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LeftSideWall;//좌측벽
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* RightSideWall;//우측벽
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* MiddleWall;//가운데 벽
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Ceiling;//천장
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LampMesh;//천장 전등

	UPROPERTY(VisibleAnywhere, Category = SpotLight)
		USpotLightComponent* LampLight;

};
