// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemyCharacter.h"
#include "GruntCharacter.generated.h"

class UStatComponent_EGrunt;
/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AGruntCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AGruntCharacter(const FObjectInitializer& ObjectInitializer);

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


	//���Ÿ� ����
	void FireAttack();

	
	const static float MaxWalkingSpeed;
	const static float MaxRunningSpeed;
	const static float MinWalkingSpeed;

	void PlayDeathEffect();
	UFUNCTION(BlueprintCallable)
	float DropExp();
	UPROPERTY(EditInstanceOnly)
	bool bAllowRandStat;

protected:
	//�׾�� �� �� ȣ��ȴ�.
	//Stat�� hp 0 delegate�� �����Ұ� �ƴ϶� anim�� dead ����� ������ ������� �ؾ߰ڱ���
	
	//���ó�� �����۾�
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
	



	//Stat Component �����Ǹ� �ű⿡ �ִ´�. ���� Ž�� ����
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
