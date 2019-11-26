// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "HPBox.generated.h"


UCLASS()
class ESCAPEGAME_API AHPBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHPBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void loadAssets();
	void initComponents();
	void setupCollision();
	//when box opened called once. 
	void setBoxStateToOpened();
private:

	
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Trigger)
		UBoxComponent* BoxCollider;
	UPROPERTY(EditInstanceOnly, Category = Mesh)
		TArray<UStaticMesh*> MeshArray;
	UPROPERTY(VisibleAnywhere, Category = Effect)
		UParticleSystemComponent* Effect;
	UPROPERTY(VisibleAnywhere, Category = Statue)
		bool bIsOpened;
};
