// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Character.h"
#include "CharacterStatComponent.h"
#include "EnemyCharacter.generated.h"



UCLASS()
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

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
		UCharacterStatComponent* Stat;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Turn(float NewAxisValue);

};
