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
		UStaticMeshComponent* Plate1;//�ٴ�
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Plate2;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall1;//������
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall2;//������
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall3;//������
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall4;//������
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Wall5;//������
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*Stair1;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*Stair2;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Ceiling;//õ��
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* CeilingDiv;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LampMesh1;//õ�� ����
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LampMesh2;//õ�� ����

	UPROPERTY(VisibleAnywhere, Category = SpotLight)
		USpotLightComponent* LampLight1;
	UPROPERTY(VisibleAnywhere, Category = SpotLight)
		USpotLightComponent* LampLight2;
	
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		AActor*Path1;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		AActor*Path2;
};
