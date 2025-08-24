// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseStruct.h"
#include "RightAnglePath.generated.h"

class USpotLightComponent;

UCLASS()
class ESCAPEGAME_API ARightAnglePath : public ABaseStruct
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARightAnglePath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	/*virtual void Tick(float DeltaTime) override;*/

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Plate;//�ٴ�
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LeftSideWall;//������
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* RightSideWall;//������
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Ceiling;//õ��
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* LampMesh;//õ�� ����

	UPROPERTY(VisibleAnywhere, Category = SpotLight)
		USpotLightComponent* LampLight;
};
