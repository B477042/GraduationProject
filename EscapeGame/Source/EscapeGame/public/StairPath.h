// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "StairPath.generated.h"

UCLASS()
class ESCAPEGAME_API AStairPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStairPath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void InitUPropertys();
	bool LoadAssets();
	void SettingWorldMatrix();
	void MakeComponentsTree();

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*Root;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Plate1;//바닥
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Plate2;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall1;//좌측벽
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall2;//좌측벽
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall3;//좌측벽
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall4;//좌측벽
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall5;//좌측벽
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*Stair1;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*Stair2;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Ceiling;//천장
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* CeilingDiv;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LampMesh1;//천장 전등
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LampMesh2;//천장 전등

	UPROPERTY(VisibleAnywhere, Category = SpotLight)
		USpotLightComponent* LampLight1;
	UPROPERTY(VisibleAnywhere, Category = SpotLight)
		USpotLightComponent* LampLight2;
	
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		AActor*Path1;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		AActor*Path2;
};
