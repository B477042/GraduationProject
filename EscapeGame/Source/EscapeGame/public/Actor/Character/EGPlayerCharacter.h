// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacterBase.h"
#include "EGPlayerCharacter.generated.h"

//DECLARE_DELEGATE(FOnKeyPressed);

class UEGCharacterAttributeSet;
class USkillContainer_PlayerFury;
class UAIPerceptionStimuliSourceComponent;
class USkillContainer_PlayerHitEffect;
class UBoxComponent;
class UMiniMapRenderComponent;
class UCameraComponent;
class USpringArmComponent;
class UComponent_Stamina;
class UComponent_TimeLimit;
class UComponent_Fury;
class UComponent_Inventory;
class UStatComponent_Player;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeHugeDamage);

UENUM(BlueprintType)
enum class ERestricInputType : uint8
{
	//Left Mouse Button
	E_LMB = 0 UMETA(DisplayName="Left Mouse Button") ,
	//Right Mouse Button
	E_RMB UMETA(DisplayName="Right Mouse Button"),
	//Both Mouse Button
	E_LRMB UMETA(DisplayName="Both Mouse Button"),
	//Axis Input Moving
	E_AxisMoving UMETA(DisplayName = "Axis Input Moving")
};


UCLASS()
class ESCAPEGAME_API AEGPlayerCharacter : public AGameCharacterBase
{
	GENERATED_BODY()

public:
	
	AEGPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	
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
	
	//============================================
	//Actions
	 void ChargeAttack();
	 void ComboAttack();
	 void AirAttack();
	 void SlashAttack();
	 void StartRunning();
	 void OnStaminaTicking();
	 void StopRunning();
	 void Roll();
	 void UseRecoveryItem();
	 void ToggleMap();
	 void PressGuard();
	 void ReleaseGuard();

	 //============================================
	 //Fury Effect

	 //True : Extend Fury Arm effect to 2.3, False : Deactivate
	 void ToggleFuryArmExtend(bool bResult);
	 //True : Activate, False : Deactivate
	 void ToggleFuryLeftArm(bool bResult);
	 //True : Activate, False : Deactivate
	 void ToggleFuryRightArm(bool bResult);
	 //Scan Enemy around Player to Apply Damage. Range 10m. Box Size W=10m, H = 2m
	 void ActiveFuryDamage();

	 //============================================
	 //Componenet
	 UStatComponent_Player* GetStatComponent()const;
	 UComponent_Inventory* GetInventory()const;
	 UComponent_Fury* GetFuryComponent()const;
	 UComponent_TimeLimit* GetTimeLimitComponent()const;
	 UComponent_Stamina* GetStaminaComponenet()const;

	 void ActiveThunder();
	 
	 UFUNCTION(BlueprintCallable)
	 void RestrictInput(const ERestricInputType& Type );
	 
	 UFUNCTION(BlueprintCallable)
	 void RecoverInput(const ERestricInputType& Type);
	 
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
	void LoadPlayerSkillObjects();
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
	void PressFury();
	/*
	 * Reflact All Projectile Type Attack
	 * 
	 */
	void OnMakeNoiseEvent();



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
			UComponent_Fury* FuryComponent;
	/*
	*	Time Limit	
	*/
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "TimeLimit", meta = (AllowPrivateAccess = true))
			UComponent_TimeLimit* TimeLimitComponent;
	/*
	*	Stamina
	*/
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Stamina", meta = (AllowPrivateAccess = true))
			UComponent_Stamina* StaminaComponent;
	/*
	* AI
	*/
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Ai Perception", meta = (AllowPrivateAccess = true))
			UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource;
	/*
	*	Fury Effect
	*/
		UPROPERTY(VisibleAnywhere, Category = "FuryParticle")
			UParticleSystemComponent* PS_FuryArmRight;
		UPROPERTY(VisibleAnywhere, Category = "FuryParticle")
			UParticleSystemComponent* PS_FuryArmLeft;
		UPROPERTY(VisibleAnywhere, Category = "Fury")
			USkillContainer_PlayerFury* Container_Fury;
	float minMiniMapArmLength;
	float maxMiniMapArmLength;
	bool bSetMapArm;

	
  
	UPROPERTY(VisibleInstanceOnly,  Category = Anim, Meta=(AllowPrivateAccess=true))
		class UAnim_Player* Anim;
	UPROPERTY(VisibleInstanceOnly, Category = "SkillActor", meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<class ASkillActor_ThunderType> Skill_Thunder;

	//디버그 모드면 플레이어는 죽지 않는다
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	bool bIsDebugMode;
	//가드
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
		bool bIsGuarding;
	//=============================================
	//Moving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Direction", meta = (AllowPrivateAccess = "true"))
		FVector MoveDirection;
	float CurrentVelocity;

	/*
	*  Restric input 
	*/
	bool bRestricAxisInput=false;
	bool bResticLMBInput=false;
	bool bRestricRMBInput = false;
	
};
