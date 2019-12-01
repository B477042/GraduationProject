// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include"EscapeGame.h"
#include"EGPlayerCharacter.h"
#include "Claymore.generated.h"

/**
 * Claymore�� �̿��� ����
	Player�� �ٰ����� ������ �Ѵ�
	
	Ÿ�̸Ӵ� 0.5�� �̳���
	�ݰ��� �ִ� �������� �ִ� �ݰ��� 5����
	�ִ� ������ 10���ͷ�
	
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
