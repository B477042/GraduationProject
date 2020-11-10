// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Character.h"
#include "StatComponent_Enemy.h"
#include "Components/WidgetComponent.h"
#include "ProgressBar.h"
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
	virtual void BeginDestroy()override;
	virtual void PostInitializeComponents() override;
	/*UFUNCTION(BlueprintCallable)
		float GetCurrentSpeed();*/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,class AController* EventInstigator, AActor* DamageCauser)override;
	UFUNCTION(BlueprintCallable)
		void Dead();


	UFUNCTION()
		void SaveGame(class UEGSaveGame* SaveInstance );
	UFUNCTION()
		void LoadGame(const class UEGSaveGAme* LoadInstance);	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Turn(float NewAxisValue);

	//Change Name if need. reefed at GruntChara, BTTask Attack. 
	//UFUNCTION(BlueprintNativeEvent)
	virtual void Attack() PURE_VIRTUAL(AEnemyCharacter::Attack,);

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowClasses))
		class UWidgetComponent* HPBarWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowClasses))
		UProgressBar*HPBar;



};
