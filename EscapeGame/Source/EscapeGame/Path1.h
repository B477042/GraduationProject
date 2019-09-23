// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include"Engine/PointLight.h"
#include "GameFramework/Actor.h"
#include "Path1.generated.h"


//Normal Hallway to Connnect Section to Section.
//Nothing Special Action in Path. 
//Add Small Point Light 

UCLASS()
class ESCAPEGAME_API APath1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APath1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//==================================
	//UPROPERTY
private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* BaseOfPath;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Ceiling;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LeftSideWall;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* RightSideWall;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* BodyOfLight;
	UPROPERTY(VisibleAnywhere, Category = PointLight)
		UPointLightComponent* PointLight;
		


};
