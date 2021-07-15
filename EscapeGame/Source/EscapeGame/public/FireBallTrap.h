// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TrapType.h"
#include "FireBallActor.h"
#include "GameFramework/Actor.h"
#include "FireBallTrap.generated.h"

//DECLARE_DELEGATE(FOnCharacterEntered,void);

UCLASS()
class ESCAPEGAME_API AFireBallTrap : public ATrapType
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBallTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void initComponents();
	void setupCollision();
	void Fire();

	UFUNCTION()
		void OnPlayerEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
private:
	UPROPERTY(VisibleAnywhere, Category = Fire)
		TWeakObjectPtr<AFireBallActor> FireBall;
	UPROPERTY(VisibleAnywhere, Category = Collision)
		UBoxComponent* Trigger;
	UPROPERTY(VisibleAnywhere,Category=mesh)
		UStaticMeshComponent*  Root;
	UPROPERTY(VisibleAnywhere, Category = mesh)
		UStaticMeshComponent*FirePoint;
};
