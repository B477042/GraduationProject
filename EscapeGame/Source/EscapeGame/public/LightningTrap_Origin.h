// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "LightningTrap_Origin.generated.h"

UCLASS()
class ESCAPEGAME_API ALightningTrap_Origin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightningTrap_Origin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/*UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
*/
protected:
	void initComponents();
	void loadAssets();
	void setRelativeCoordinates();
	void setupCollision();
	void setupMemberVariables();

	bool Activate();
	bool Decativate();

	//액션을 위한 타이머
	float Timer;
	
	
protected:
	
	UPROPERTY(VisibleAnywhere, Category = mesh)
		UStaticMeshComponent*LeftMesh;
	UPROPERTY(VisibleAnywhere, Category = mesh)
		UStaticMeshComponent*RightMesh;
	UPROPERTY(VisibleAnywhere, Category = Collision)
		UCapsuleComponent*CapsuleCollision;
	UPROPERTY(VisibleAnywhere, Category = mesh)
		UParticleSystemComponent* Effect;
	//on, off 사이의 간격
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float IntervalTimer;
	//effect가 작동하는 시간
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float ActveTimer;
	UPROPERTY(EditInstanceOnly, Category = Contents)
		bool bIsActve;
	
};
