// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "SmokeTrap.generated.h"


/*
	연기형 함정

*/
UCLASS()
class ESCAPEGAME_API ASmokeTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmokeTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	const float ReActTimer = 0.5f;
private:
	UFUNCTION()
		void OnCharacterEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Particle)
		UParticleSystemComponent* Effect;
	UPROPERTY(VisibleAnywhere, Category = Damage)
		float Damage;
	UPROPERTY(VisibleAnywhere, Category = Timer)
		float Timer;

};
