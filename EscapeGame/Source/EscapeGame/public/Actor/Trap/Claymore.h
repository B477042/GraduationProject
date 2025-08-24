// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "TrapType.h"

#include "Claymore.generated.h"

/**
 * Claymore�� �̿��� ����
	Player�� �ٰ����� ������ �Ѵ�
	
	Ÿ�̸Ӵ� 0.5�� �̳���
	�ݰ��� �ִ� �������� �ִ� �ݰ��� 5����
	�ִ� ������ 10���ͷ�
	
 */

/*
void DrawDebugBox
(
    const UWorld * InWorld,
    FVector const & LineStart,
    FVector const & LineEnd,
    FColor const & Color,
    bool bPersistentLines,
    float LifeTime,
    uint8 DepthPriority,
    float Thickness
)
*/

class AEGPlayerCharacter;
class UBoxComponent;
DECLARE_MULTICAST_DELEGATE(FOnExplosion);

UCLASS()
class ESCAPEGAME_API AClaymore : public ATrapType
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
	FVector getNormalVectorDistance(const FVector* Other);
	float getDistanceToTarget();
	float getDamage();
	
	//�ڽ��� ũ�⸦ �������� ����
	bool bIsActorInFrontSide(FHitResult& hitResult);
	//�ڽ��� ũ�⸦ �������� ����
	void changeBoxExtent(const FHitResult& hitResult);
	
	
private:
	const float maxDamageRange = 200.0f;
	const float minDamageRange = 300.0f;
	const float maxDetectRange = 200.0f;

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
	UPROPERTY(VisibleAnywhere, Category = Content)
		UAudioComponent* AudioEffect;
	UPROPERTY(VisibleAnywhere, Category = Content)
		UAudioComponent* SwitchClickSound;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float MinDamage;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float MaxDamage;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float Timer;
	
	UPROPERTY(EditInstanceOnly, Category = Statue)
		bool bIsActive;
	

};
