// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "SkillActor.h"
#include "Projectile.generated.h"

/*
	발사체 클래스
*/
UCLASS()
class ESCAPEGAME_API AProjectile : public  ASkillActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	virtual void ReadyToFire(const FVector &Dir_Vector, const FVector& Location,const FRotator& Rotate);
	void Fire();
	virtual void PostInitializeComponents()override;
	//메인 이펙트에 맞았을 때
	UFUNCTION()
	void OnSomethingHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	//옆으로 지나갈 때

	//반사되었을때
	UFUNCTION()
		void Reflected();

	UFUNCTION()
	void OnCharacterEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	
	void TripleDamage() { Damage *= 3.0f; }

	void SetCollision(const FName&name) { Collision->SetCollisionProfileName(name); }
	UFUNCTION(BlueprintCallable)
		void BP_Fire(FVector Location, FRotator Rotation, FVector Dir);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void gliding();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	


};
