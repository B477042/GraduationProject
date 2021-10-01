// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemyCharacter.h"
#include "Anim_Grunt.h"
#include "StatComponent_EGrunt.h"
#include "Components/AudioComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "GruntCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AGruntCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AGruntCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;


	virtual void SaveGame(class UEGSaveGame* SaveInstance)override;

	virtual void LoadGame(const class UEGSaveGame* LoadInstance)override;


	void PlayMuzzleEffect();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attack()override;


	//원거리 공격
	void FireAttack();

	
	const static float MaxWalkingSpeed;
	const static float MaxRunningSpeed;
	const static float MinWalkingSpeed;

	void PlayDeathEffect();
	UFUNCTION(BlueprintCallable)
		float DropExp() { return StatComponent->GetDropExp(); }
	UPROPERTY(EditInstanceOnly)
	bool bAllowRandStat;

protected:
	//죽어야 될 때 호출된다.
	//Stat의 hp 0 delegate에 연동할게 아니라 anim의 dead 모션이 끝나면 사라지게 해야겠구나
	
	//사망처리 사전작업
	UFUNCTION()
		void ReadToDead();
	
	UPROPERTY(EditInstanceOnly, Category = "Stat")
	UStatComponent_EGrunt* StatComponent;
	UPROPERTY(EditInstanceOnly, Category = "SFX")
	UAudioComponent* SFX_Explosion;
	UPROPERTY(EditInstanceOnly, Category = "SFX")
	UAudioComponent* SFX_Burst;
	UPROPERTY(EditInstanceOnly, Category = "SFX")
	UAudioComponent* SFX_Death;
	UPROPERTY(EditInstanceOnly, Category = "VFX")
	UParticleSystemComponent* VFX_MuzzleEffect;
	UPROPERTY(EditInstanceOnly, Category = "VFX")
	UParticleSystemComponent* VFX_HitEffect;
	



	//Stat Component 정리되면 거기에 넣는다. 전방 탐지 범위
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
		float MeleeAttackRange;
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
		FVector MeleeAttackExtent;
	//Melee Attack Value
	float AtkMeleeAtk;
	//Fire Attack Value
	float AtkFireAtk;

	const FName SockFirePointR = "fire_point_r";
	class UAnim_Grunt* Anim;
};
