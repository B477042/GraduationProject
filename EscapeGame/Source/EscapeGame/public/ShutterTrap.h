// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include"SpearActor.h"
#include "ShutterTrap.generated.h"


DECLARE_DELEGATE_OneParam (FOnSpearDurabilityChange, TWeakObjectPtr<ASpearActor>)

UCLASS()
class ESCAPEGAME_API AShutterTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShutterTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FOnSpearDurabilityChange SpearDuabilityChangedDelegate;
	void OnPlayerEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	void RiseUpSpears();
private:
	void initComponents();
	void loadAssets();
	void setupCollision();

	

	const float DelayTime = 0.3f;
private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent*Root;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		 TArray<TWeakObjectPtr<ASpearActor>> Spears;
	UPROPERTY(VisibleAnywhere, Category = Sounds)
		UAudioComponent* SoundEffect;

	UPROPERTY(VisibleAnywhere, Category = Collision)
		UBoxComponent* Trigger;

	UPROPERTY(EditInstanceOnly, Category = Contents)
		float Timer;
	UPROPERTY(EditInstanceOnly, Category = Contents)
		bool bIsActivated;
	
};
