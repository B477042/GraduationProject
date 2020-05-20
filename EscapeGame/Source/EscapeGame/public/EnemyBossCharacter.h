// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemyCharacter.h"
#include "SkillComponent_ProjectileType.h"
#include "EnemyBossCharacter.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBossState:uint8
{
	Walk=0,
	Dash
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireballThrow);

UCLASS(BlueprintType)
class ESCAPEGAME_API AEnemyBossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:

	AEnemyBossCharacter();
	virtual void BeginPlay()override;
	
	//float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);
	virtual void PostInitializeComponents()override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	
	//BT���� Attack ����� �������� �� ȣ��ȴ�
	UFUNCTION()
	virtual void Attack()override;

	void SetState(EBossState NewState) { State = NewState; }
	EBossState GetState() { return State; }

	UFUNCTION(BlueprintCallable, Category = "Custom")
		void ThrowFireBall();

	UPROPERTY(BlueprintAssignable)
		FOnFireballThrow OnFireballThrow;

private:
	void initComponents();
	void loadAsset();
	void attachParticle();


private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bIsDamaged;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EBossState State;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkillComponent_ProjectileType* Comp_Fireball;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FName,USoundWave*> SoundMap;

};
