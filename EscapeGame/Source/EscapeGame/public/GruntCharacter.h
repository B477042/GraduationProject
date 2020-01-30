// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemyCharacter.h"
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
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere,Category=Animation)
		class UCharacterAnimInstance* Anim;
};
