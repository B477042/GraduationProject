// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemyCharacter.h"
#include "EnermyBossCharacter.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ESCAPEGAME_API AEnermyBossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:

	AEnermyBossCharacter();

	
	//float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);
	virtual void PostInitializeComponents()override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	
	//BT에서 Attack 명령이 떨어졌을 때 호출된다
	UFUNCTION()
	virtual void Attack()override;

private:
	void initComponents();
	void loadAsset();



private:
	UPROPERTY(BlueprintReadWrite,  meta = (AllowPrivateAccess = "true"))
		bool bIsDamaged;

};
