// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "SkillActor.generated.h"



UCLASS()
class ESCAPEGAME_API ASkillActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillActor();

	UFUNCTION(BlueprintCallable)
	virtual void ActivateHitEffect();
	UFUNCTION(BlueprintCallable)
	void ActivateMainEffect();
	UFUNCTION(BlueprintCallable)
	virtual void SetSafety(UParticleSystemComponent* PSystem);
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Root;

	//형태로 사용될 수 있는 주된 이펙트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "effect")
	UParticleSystemComponent* VFX_Main;

	//명중시 이펙트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "effect")
	UParticleSystemComponent* VFX_Hit;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	USphereComponent* MainCollision;

	//맞으면 나는 소리
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Contents")
	UAudioComponent* SFX_Hit;
	//주변에서 나는 소리
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Contents")
	UAudioComponent* SFX_Passing;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = Info)
		float Damage;

	


};
