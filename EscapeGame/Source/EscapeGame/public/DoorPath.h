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
	virtual void PostInitializeComponents()override;
private:
	void SetRelativePos();
	UFUNCTION()
		void OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Door1;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*Door2;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*DoorGate;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Trigger;
};
