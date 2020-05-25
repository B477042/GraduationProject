// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemyCharacter.h"
#include "SkillComponent_ProjectileType.h"
#include "StatComponent_Enemy.h"
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

DECLARE_MULTICAST_DELEGATE(FOnTeleportCalled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireballThrow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossIsDeadDelegate);

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
	
	//BT에서 Attack 명령이 떨어졌을 때 호출된다
	UFUNCTION()
	virtual void Attack()override;
	UFUNCTION(BlueprintCallable)
		virtual bool TeleportTo(const FVector & DestLocation,const FRotator & DestRotation,	bool bIsATest,	bool bNoCheck);



	void SetState(EBossState NewState) { State = NewState; }
	EBossState GetState() { return State; }

	UFUNCTION(BlueprintCallable, Category = "Custom")
		void ThrowFireBall();

	UPROPERTY(BlueprintAssignable)
		FOnFireballThrow OnFireballThrow;
	UPROPERTY(BlueprintAssignable)
	FOnBossIsDeadDelegate OnBossIsDead;

	FOnTeleportCalled OnTeleportCalled;

	UStatComponent_Enemy* GetStat() { return Stat; }

private:
	void initComponents();
	void loadAsset();
	void attachParticle();
	void reloadSkillObjs();

UFUNCTION(BlueprintCallable)
		void ReadyToDie();
	UFUNCTION(BlueprintCallable)
		void Die();
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStatComponent_Enemy* Stat;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bIsDamaged;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EBossState State;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkillComponent_ProjectileType* Comp_Fireball;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FName,USoundWave*> SoundMap;

};
