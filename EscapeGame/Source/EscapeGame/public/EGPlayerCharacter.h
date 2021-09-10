// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MinimapRenderComponent.h"
#include "GameFramework/Character.h"
#include "StatComponent_Player.h"
#include "Anim_Player.h"
#include "Component_Inventory.h"
#include "SkillContainer_PlayerHitEffect.h"
#include "Components/BoxComponent.h"
#include "EGPlayerCharacter.generated.h"

//DECLARE_DELEGATE(FOnKeyPressed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeHugeDamage);

UCLASS()
class ESCAPEGAME_API AEGPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AEGPlayerCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	void HealHP(float addHP);
	
	
	//Actions
	 void ChargeAttack();
	 void ComboAttack();
	 void AirAttack();
	 void StartRunning();
	 void UsingStaminaTick();
	 void StopRunning();
	 void Roll();
	 void UseRecoveryItem();
	 void ToggleMap();
	 void PressGuard();
	 void ReleaseGuard();

	
	 UStatComponent_Player* GetStatComponent();
	 UComponent_Inventory* GetInventory();

	 
	 void ActiveThunder();
	 //User Input Disable
	 UFUNCTION(BlueprintCallable)
	 void RestricInput();
	 //User Input Enable
	 UFUNCTION(BlueprintCallable)
	 void RecoverInput();
	 
	 //Over 10 Damage -> Reacting
	 UPROPERTY(BlueprintAssignable)
	 FOnTakeHugeDamage OnTakeHugeDamageDelegate;
 
public:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = Stat)
	UStatComponent_Player* Stat;
	UPROPERTY(VisibleAnywhere, Category = "inventory")
	UComponent_Inventory* Inventory;

	
private:
	void InitComponents();
	void LoadAssets();
	void LoadHitEffects();
	//void SetupMiniMap();
	//=========================
	//Camera Category Init Functions
	void SetupSpringArm();
	//void SetupCamera();
	//=========================
	//Axis Input Functions
	void UpDown(float NewAxisValue);
	void LeftRight( float NewAxisValue);
	void LookUp( float  NewAxisValue);
	void Turn( float NewAxisValue);
	//=========================
	//Action Input Functions
	virtual void Jump()override;
	//=========================
	void KeyInputTest();

	//======================
	void SetDeath();

	void Move(float DeltaTime);

	/*
	 * Reflact All Projectile Type Attack
	 * 
	 */
	float ReflectProjectiles(AActor* DamageCauser, float FinalDamage);

	void OnNextStage(const class UEGSaveGame* LoadInstance);

	//현재 체력에 따라 카메라에 이펙트를 준다. HP가 변하면 업데이트가 되게끔
	void DamagedPostEffect();


	UFUNCTION(BlueprintCallable)
	void LoadGameData(const class UEGSaveGame* LoadInstance);

	UFUNCTION()
		void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	//============================
	UFUNCTION(BlueprintCallable)
		void OnCheckCanComboAttack(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void OnAttackMontageStart(UAnimMontage* Montage);
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	//Attack Montage�� ����� �� ȣ��� �Լ�
	UFUNCTION()
		void ComboAttackStart();
	//Montage�� ���� �� ȣ��� �Լ�
	UFUNCTION()
		void ComboAttackEnd();
	//Return Name of Hit Direction
	UFUNCTION(BlueprintCallable)
		FName CalcHitDirection(AActor* DamageCauser);

	
//==================================================
	protected:
		//Main Cam Spring Arm Values
		float ArmLengthTo = 0.0f;
		FRotator ArmRotationTo = FRotator::ZeroRotator;
		float ArmLengthSpeed = 0.0f;
		float ArmRotationSpeed = 0.0f;

	/*
	 *=====================================================
	 * Main Camera Components
	 */
		UPROPERTY(VisibleAnywhere, Category = MainCam)
		USpringArmComponent* SpringArm;
		UPROPERTY(VisibleAnywhere, Category = MainCam)
		UCameraComponent* Camera;

	/*
	 *=====================================================
	 * MiniMap
	 */
		UPROPERTY(VisibleAnywhere, Category = MiniMap)
		USpringArmComponent* MiniMapArm;
		UPROPERTY(VisibleAnywhere, Category = MiniMap)
		UMiniMapRenderComponent* MapRenderer;
		/*미니맵에 표시되는 Marker용 */
		UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "MiniMap", meta = (AllowPrivateAccess = true))
		class UMiniMapMarkerComponent* MiniMapMarkerComponent;

	/*
	 *======================================================
	 * Weapon Component
	 */
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponBox", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* WeaponCollision;
		//SoundCue'/Game/ParagonKwang/Characters/Heroes/Kwang/Sounds/SoundCues/Kwang_Effort_Attack.Kwang_Effort_Attack'
		UPROPERTY(VisibleAnywhere, Category = "Sound")
		UAudioComponent* AttackSound;
		UPROPERTY(VisibleAnywhere, meta = (AllowClasses))
		USkillContainer_PlayerHitEffect* Container_Hit;
		UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* SwordEffect;
		UPROPERTY(VisibleAnywhere, Category = "Effect")
		class UBarrierEffectComponent* BarrierEffect;


	/*
	* Fury System	
	*/
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Fury", meta = (AllowPrivateAccess = true))
			class UComponent_Fury* FuryComponent;


	float minMiniMapArmLength;
	float maxMiniMapArmLength;
	bool bSetMapArm;

	float CurrentVelocity;
  
	UPROPERTY(VisibleInstanceOnly,/*BlueprintReadOnly,*/ Category = Anim, Meta=(AllowPrivateAccess=true))
		class UAnim_Player* Anim;
	UPROPERTY(VisibleInstanceOnly, Category = "SkillActor", meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<class ASkillActor_ThunderType> Skill_Thunder;

	//디버그 모드면 플레이어는 죽지 않는다
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	bool bIsDebugMode;
	//가드하고 있으면 투사체를 튕겨낸다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
		bool bIsGuarding;

	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Direction", meta = (AllowPrivateAccess = "true"))
		FVector MoveDirection;


};
