// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemyCharacter.h"
#include "SkillComponent_ProjectileType.h"
#include "StatComponent_Enemy.h"
#include "Animation/AnimMontage.h"
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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOChargeCalled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireballThrow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossIsDeadDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThunderbolt);

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

	UFUNCTION(BlueprintCallable, Category = "Custom")
		void ThrowFireBall();
	UFUNCTION(BlueprintCallable)
		void Thunderbolt();
	//Thunderbolt가 플레이될 때 실행시킬 것
	UFUNCTION(BlueprintCallable)
		void AtPlayThunderblotAnim();
	UFUNCTION(BlueprintCallable)
	void ChargeMP();



	void SetState(EBossState NewState) { State = NewState; }
	EBossState GetState() { return State; }

	UPROPERTY(BlueprintAssignable)
		FOnThunderbolt OnThunderbolt;
	UPROPERTY(BlueprintAssignable)
		FOnFireballThrow OnFireballThrow;
	UPROPERTY(BlueprintAssignable)
	FOnBossIsDeadDelegate OnBossIsDead;
	UPROPERTY(BlueprintAssignable)
	FOChargeCalled OnChargeCalled;

	FOnTeleportCalled OnTeleportCalled;

	UStatComponent_Enemy* GetStat() { return Stat; }

	void SetCharging(bool bResult) { bIsMpCharging = bResult; }
	void PlayChargeEffect(bool Power);




protected:
	void initComponents();
	void loadAsset();

	void reloadSkillObjs();
	virtual void SaveGame(class UEGSaveGame* SaveInstance)override;

	virtual void LoadGame(const class UEGSaveGame* LoadInstance)override;

//UFUNCTION(BlueprintCallable)
//		void ReadyToDie();
//	UFUNCTION(BlueprintCallable)
//		void Die();
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStatComponent_Enemy* Stat;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bIsDamaged;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EBossState State;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkillComponent_ProjectileType* Comp_Fireball;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* TeleportEnter;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* TeleportExit;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UAudioComponent* TeleportSound;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		 TWeakObjectPtr<class ASkillActor_BossLightning> SA_Thunder;

	//MPHealing Motion
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* MpChargingEffect;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* MpChargingSound;

	//MP를 충전하는지
	UPROPERTY(BlueprintReadWrite, Category = "Mp", meta = (AllowPrivateAccess = "true"))
	bool bIsMpCharging;



/*


	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FName,USoundBase*> SoundMap;*/



};
