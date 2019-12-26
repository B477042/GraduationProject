// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "SpearActor.h"
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
	virtual void PostInitializeComponents()override;
	FOnSpearDurabilityChange SpearDuabilityChangedDelegate;
	
	void RiseUpSpears(float deltaTime);
	UFUNCTION()
		void OnPlayerEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
private:
	void initComponents();
	void loadAssets();
	void setupCollision();

	
	void setSpearsDefaultPos();


	const float StreachTime = 0.3f;
	const int n_spears = 4;
	const float spear_start = -120.0f;
	const float spear_last = 12.0f;
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
