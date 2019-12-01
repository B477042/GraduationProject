// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include"EscapeGame.h"
#include"EGPlayerCharacter.h"
#include "Claymore.generated.h"

/**
 * Claymore를 이용한 함정
	Player가 다가가면 터지게 한다
	
	타이머는 0.5초 이내로
	반경은 최대 데미지를 주는 반경은 5미터
	최대 범위는 10미터로
	
 */

DECLARE_MULTICAST_DELEGATE(FOnExplosion);

UCLASS()
class ESCAPEGAME_API AClaymore : public AActor
{
	GENERATED_BODY()
public:
	AClaymore();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents()override;
public:

	FOnExplosion ExplosionDelegate;


	

private:
	void initComponents();
	void loadAssets();
	void setRelativeCoordinates();
	void setupCollision();

	
	void explosion();
	FVector getNormalVectorDistance();
	float getDistance();
	float getDamage();
	
	//float get
private:
	const float maxDamageRange = 200.0f;
	const float minDamageRange = 300.0f;
	

	TWeakObjectPtr<AEGPlayerCharacter> target;
	
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
		void ClearMe(UParticleSystemComponent* Particle);
private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UParticleSystemComponent* Effect;
	UPROPERTY(VisibleAnywhere, Category = Collision)
		UBoxComponent*BoxCollision;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float MinDamage;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float MaxDamage;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float Timer;
	UPROPERTY(EditInstanceOnly, Category = Statue)
		bool bIsActive;
	
};
