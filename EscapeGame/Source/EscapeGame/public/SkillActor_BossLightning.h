// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "SkillActor.h"
#include "Components/CapsuleComponent.h"
#include "SkillActor_BossLightning.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API ASkillActor_BossLightning : public ASkillActor
{
	GENERATED_BODY()
public:

	ASkillActor_BossLightning();

public:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	bool UseSkill(const FVector& Loc, const FRotator& Rot);

	bool IsActivate() { return bIsActivated; }
	//���� �߻��Ѵ�
	UFUNCTION()
	void ActivateEffect();
	UFUNCTION()
	void DeactivateEffect();

protected:

	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	

private:

	void loadAsset();
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* Capsule;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		bool bIsActivated;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float Timer;
	UPROPERTY(meta = (AllowPrivateAccess = "true"))
		float Limit;
	
	
};
