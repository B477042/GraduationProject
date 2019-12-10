// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "FireBallActor.generated.h"

UCLASS()
class ESCAPEGAME_API AFireBallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBallActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents()override;
	void Fire(FRotator Direction);
private:
	void initComponents();
	void loadAssetes();
	void setupCollision();
	

	void setCollisionProfile(FName NewProfile);
	UFUNCTION()
		void OnCharacterHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
		void OnCharacterEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
		void destroyMe();
	float flyingTime;


private:
	
	UPROPERTY(VisibleAnywhere, Category = effect)
		UParticleSystemComponent* FireBall;
	UPROPERTY(VisibleAnywhere, Category = effect)
		UParticleSystemComponent* ExplosionEffect;
	UPROPERTY(VisibleAnywhere, Category = effect)
		UParticleSystemComponent* HitEffect;
	UPROPERTY(VisibleAnywhere, Category = Collision)
		USphereComponent*Collision;
	UPROPERTY(VisibleAnywhere, Category = Collision)
		USphereComponent*SoundTrigger;


	UPROPERTY(VisibleAnywhere, Category = Contents)
		UAudioComponent*SoundExplosion;
	UPROPERTY(VisibleAnywhere, Category = Contents)
		UAudioComponent*SoundCast;
	UPROPERTY(VisibleAnywhere, Category = Speed)
		bool bIsFlying;

	UPROPERTY(EditInstanceOnly, Category = Damage)
		float Damage;
	UPROPERTY(EditInstanceOnly, Category = Speed)
		float Speed;
	UPROPERTY(VisibleAnywhere, Category = Speed)
		float LimitSpeed;
	UPROPERTY(EditInstanceOnly, Category = Speed)
		FRotator direction;
};
