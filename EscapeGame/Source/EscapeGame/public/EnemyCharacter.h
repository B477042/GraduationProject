// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Character.h"
#include "StatComponent_Enemy.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

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


	//Save Game 단계에서Enemy Character들이 공통적으로 저장할 정보를 저장한다. Delegate 등록은 자식 클레스에서
	UFUNCTION(BlueprintCallable)
	virtual	void SaveGame(class UEGSaveGame* SaveInstance);
	//Load Game 단계에서 Enemmy Character들이 공통적으로 저장할 정보를 저장한다. Delegate 등록은 자식 클레스에서
	UFUNCTION(BlueprintCallable)
	virtual	void LoadGame(const class UEGSaveGame* LoadInstance);
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* HPBarWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UProgressBar*HPBar;

	
	
	/*
	https://docs.unrealengine.com/en-US/API/Runtime/AIModule/Perception/UAIPerceptionComponent/index.html
	자손 클래스에서 값 처리를 시킬 것
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;

};
