// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "SkillActor.generated.h"



UCLASS()
class ESCAPEGAME_API ASkillActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillActor();

	UFUNCTION()
	void ActivateHitEffect();
	UFUNCTION()
	void ActivateMainEffect();
	UFUNCTION()
	void SetSafety();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

	//
	
	void initComponents();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, Category = effect)
	UParticleSystemComponent* MainEffect;
	UPROPERTY(VisibleAnywhere, Category = effect)
	UParticleSystemComponent* ReactEffect;
	UPROPERTY(VisibleAnywhere, Category = effect)
	UParticleSystemComponent* HitEffect;
	UPROPERTY(VisibleAnywhere, Category = Collision)
	USphereComponent*Collision;

	UPROPERTY(VisibleAnywhere, Category = Collision)
	USphereComponent*SoundTrigger;//볼이 날아갈 때 옆에 지나가면 날아가는 소리가 들리게끔 하는 범위
		//맞으면 나는 소리
	UPROPERTY(VisibleAnywhere, Category = Contents)
	UAudioComponent*SoundHit;
	//날아가면서 나는 소리
	UPROPERTY(VisibleAnywhere, Category = Contents)
	UAudioComponent*SoundPassing;

protected:

	UPROPERTY(VisibleAnywhere)
	bool bIsFire;
	//발사방향
	UPROPERTY(VisibleAnywhere)
	FVector FireDir;
	//속도
	UPROPERTY(VisibleAnywhere)
	float Acceleration;
	UPROPERTY(VisibleAnywhere)
	float Damage;


};
