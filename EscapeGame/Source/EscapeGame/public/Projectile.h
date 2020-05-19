// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

/*
	�߻�ü Ŭ����
*/
UCLASS()
class ESCAPEGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	virtual void ReadyToFire(const FVector &Dir_Vector, const FVector& Location,const FRotator& Rotate);
	virtual void PostInitializeComponents()override;
	//���� ����Ʈ�� �¾��� ��
	UFUNCTION()
	void OnSomethingHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	//������ ������ ��

	UFUNCTION()
	void OnCharacterEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
	void ActivateEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void setSafety();
	void gliding();
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
	USphereComponent*SoundTrigger;//���� ���ư� �� ���� �������� ���ư��� �Ҹ��� �鸮�Բ� �ϴ� ����
	//������ ���� �Ҹ�
	UPROPERTY(VisibleAnywhere, Category = Contents)
	UAudioComponent*SoundHit;
	//���ư��鼭 ���� �Ҹ�
	UPROPERTY(VisibleAnywhere, Category = Contents)
	UAudioComponent*SoundPassing;

protected:

	UPROPERTY(VisibleAnywhere)
	bool bIsFire;
	//�߻����
	UPROPERTY(VisibleAnywhere)
	FVector FireDir;
	//�ӵ�
	UPROPERTY(VisibleAnywhere)
	float Acceleration;
	UPROPERTY(VisibleAnywhere)
	float Damage;
};
