// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/SceneCapture2D.h"
#include "MinimapRenderComponent.h"
#include "GameFramework/Character.h"
#include "CharacterStatComponent.h"
#include "EGPlayerCharacter.generated.h"



UCLASS()
class ESCAPEGAME_API AEGPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEGPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//virtual void TickComponent(float DeltaTime)override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	//=====================================================================
	//Public Not UPROPERTY member 
public:
	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, \
		class AController* EventInstigator, AActor* DamageCauser)override;
	void HealHP(float addHP);
	 UCharacterStatComponent* GetStatComponent();
	//=====================================================================
	// Public UPROPERTY Zone
public:
	UPROPERTY(VisibleAnywhere, Category = MainCam)
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = MainCam)
		UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, Category = Minimap)
		USpringArmComponent* MiniMapArm;
	UPROPERTY(VisibleAnywhere, Category = Minimap)
		UMiniMapRenderComponent* MapRenderer;
	UPROPERTY(BlueprintReadOnly,EditInstanceOnly, Category = Stat)
		UCharacterStatComponent* Stat;
	
private:
	void InitComponents();
	void LoadAssets();
	//void SetupMiniMap();
	//=========================
	//Camera Category Init Functions
	void SetupSpringArm();
	//void SetupCamera();
	//=========================
	//Axis Input Functions
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	//=========================
	//Action Input Functions

	//=========================
	
	//========================================
	//private PROPERTY
private:
	//UPROPERTY(BlueprintReadable, Meta=privateAccessAllowd=true)

};
