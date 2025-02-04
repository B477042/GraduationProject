// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "TrapType.h"
#include "EGPlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Claymore.generated.h"

/**
 * Claymore를 이용한 함정
	Player가 다가가면 터지게 한다
	
	타이머는 0.5초 이내로
	반경은 최대 데미지를 주는 반경은 5미터
	최대 범위는 10미터로
	
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
	
	//박스의 크기를 동적으로 변경
	bool bIsActorInFrontSide(FHitResult& hitResult);
	//박스의 크기를 동적으로 변경
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
