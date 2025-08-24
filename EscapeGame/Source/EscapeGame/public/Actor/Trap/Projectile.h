// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Actor/SklillActor/SkillActor.h"
#include "Projectile.generated.h"

/*
	�߻�ü Ŭ����

	* 

*/
UCLASS()
class ESCAPEGAME_API AProjectile : public  ASkillActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	
	virtual void ReadyToFire(const FVector &Dir_Vector, const FVector& Location,const FRotator& Rotate);

	
	virtual void SetSafety(UParticleSystemComponent* PSystem)override;
	virtual void ActivateHitEffect() override;
	

	//���� ����Ʈ�� �¾��� ��
	UFUNCTION()
	void OnSomethingHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	
	UFUNCTION()
	void OnPlayerEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	

	void SetCollision(const FName&name) { MainCollision->SetCollisionProfileName(name); }

//�ݻ�Ǿ�����
	UFUNCTION()
	void Reflected();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

	void Gliding();
	void fire();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	////���ư��� ȿ���� ���� Actor�� ������ �� ���� �Ҹ��� ��� ��ų ����
	UPROPERTY(VisibleAnywhere, Category = MainCollision)
		USphereComponent*Trigger_Passing;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"),Category = FireInformation)
		bool bIsFired;
	//�߻����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = FireInformation)
		FVector FireDir;
	//�ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = FireInformation)
		float Acceleration;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = Movement)
	//UProjectileMovementComponent* MovementComponent;

	bool bIsDebugMode;
};
