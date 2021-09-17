// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "SkillActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

/*
	발사체 클래스

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
	

	//메인 이펙트에 맞았을 때
	UFUNCTION()
	void OnSomethingHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	
	UFUNCTION()
	void OnPlayerEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	

	void SetCollision(const FName&name) { MainCollision->SetCollisionProfileName(name); }

//반사되었을때
	UFUNCTION()
	void Reflected();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

	void gliding();
	void fire();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	////날아가는 효과를 가진 Actor가 지나갈 때 나는 소리를 재생 시킬 범위
	UPROPERTY(VisibleAnywhere, Category = MainCollision)
		USphereComponent*Trigger_Passing;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"),Category = FireInformation)
		bool bIsFire;
	//발사방향
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = FireInformation)
		FVector FireDir;
	//속도
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = FireInformation)
		float Acceleration;
	
	//UProjectileMovementComponent* move;

	bool bIsDebugMode;
};
