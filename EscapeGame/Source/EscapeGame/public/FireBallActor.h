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
	void Fire();

private:
	void initComponents();
	void loadAssetes();
	void setupCollision();

	
	
	

	UFUNCTION()
		void OnCharacterHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
		void OnCharacterEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
		void ExplosionMe();
	UFUNCTION()
		void DestroyMe();
	void flying(const float& DeltaTime);
	
	float flyingTime;
	const float MaxFlyingTime=4.0f;
	
private:
	//Light��������� ���� Root ������Ʈ�� ���� �� ������Ʈ
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, Category = effect)
		UParticleSystemComponent* FireBall;
	UPROPERTY(VisibleAnywhere, Category = effect)
		UParticleSystemComponent* ExplosionEffect;
	UPROPERTY(VisibleAnywhere, Category = effect)
		UParticleSystemComponent* HitEffect;
	UPROPERTY(VisibleAnywhere, Category = Collision)
		USphereComponent*Collision;

	UPROPERTY(VisibleAnywhere, Category = Collision)
		USphereComponent*SoundTrigger;//���� ���ư� �� ���� �������� ���ư��� �Ҹ��� �鸮�Բ� �ϴ� ����


	UPROPERTY(VisibleAnywhere, Category = Contents)
		UAudioComponent*SoundExplosion;
	UPROPERTY(VisibleAnywhere, Category = Contents)
		UAudioComponent*SoundCast;


	UPROPERTY(EditInstanceOnly, Category = Damage)
		float Damage;
	UPROPERTY(EditInstanceOnly, Category = Speed)
		float Speed;
	
	UPROPERTY(VisibleAnywhere, Category = Speed)
		bool bIsFlying;

	
};
