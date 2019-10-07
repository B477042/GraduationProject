// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "NormalPath.h"
#include "DoorPath.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API ADoorPath : public ANormalPath
{
	GENERATED_BODY()
public:
	ADoorPath(); 
	void OpenTheDoor();
	void CloseTheDoor();
private:
	void SetRelativePos();
	

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Door1;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*Door2;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*DoorGate;
};
