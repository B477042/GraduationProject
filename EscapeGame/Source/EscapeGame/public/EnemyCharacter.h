// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Character.h"
#include "StatComponent_Enemy.h"
#include "EnemyCharacter.generated.h"



UCLASS(Abstract)
class ESCAPEGAME_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	/*const static float MaxHP;
	const static float MaxWalkingSpeed;
	const static float MaxRunningSpeed;
	const static float MinWalkingSpeed;*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*UFUNCTION(BlueprintCallable)
		float GetCurrentSpeed();*/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,class AController* EventInstigator, AActor* DamageCauser)override;
	UFUNCTION(BlueprintCallable)
		void Dead();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Turn(float NewAxisValue);

	//Change Name if need. reefed at GruntChara, BTTask Attack. 
	//UFUNCTION(BlueprintNativeEvent)
	virtual void Attack() PURE_VIRTUAL(AEnemyCharacter::Attack,);

};
