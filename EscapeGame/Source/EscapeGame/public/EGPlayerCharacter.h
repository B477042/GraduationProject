// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/SceneCapture2D.h"
#include "MinimapRenderComponent.h"
#include "GameFramework/Character.h"
#include "StatComponent_Player.h"
#include "Anim_Player.h"
#include "Component_SelfDamage.h"
#include "Component_Inventory.h"
#include "SkillContainer_PlayerHitEffect.h"
#include "EGPlayerCharacter.generated.h"

//DECLARE_DELEGATE(FOnKeyPressed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeHugeDamage);

UCLASS()
class ESCAPEGAME_API AEGPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEGPlayerCharacter();
	 //FOnKeyPressed OnKeyPressed;
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
	 UStatComponent_Player* GetStatComponent();
	 UComponent_Inventory* GetInventory();
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
	 void SetGuard();
	 void ReleaseGuard();
	 

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
	//const AController* GetController();

	 ////===============Static Vars
	//// const static float MaxHP;
	// const static float MaxWalkingSpeed;
	// const static float MaxRunningSpeed;
	// const static float MinWalkingSpeed;

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
		UStatComponent_Player* Stat;
	UPROPERTY(EditAnywhere, Category = "Damage")
		UComponent_SelfDamage* SelfDamage;
	UPROPERTY(VisibleAnywhere, Category = "inventory")
		UComponent_Inventory* Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponBox", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* WeaponCollision;
	//SoundCue'/Game/ParagonKwang/Characters/Heroes/Kwang/Sounds/SoundCues/Kwang_Effort_Attack.Kwang_Effort_Attack'
	UPROPERTY(VisibleAnywhere, Category = "Sound")
		UAudioComponent* AttackSound;
	UPROPERTY(VisibleAnywhere, meta = (AllowClasses))
		USkillContainer_PlayerHitEffect* Container_Hit;


	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent * SwordEffect;
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


	UFUNCTION()
		void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	//============================
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
		FName calcHitDirection(AActor* DamageCauser);


	/*UFUNCTION()
		void ChargeAttackStart();
	UFUNCTION()
		void ChargeAttackEnd();*/

//==================================================
	float minMapArmLength;
	float maxMapArmLength;
	bool bSetMapArm;

	void loadHitEffects();
	//private PROPERTY
private:

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

};
