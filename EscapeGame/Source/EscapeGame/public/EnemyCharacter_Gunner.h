// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EnemyCharacter.h"
#include "Component_Mag.h"
#include "Components/AudioComponent.h"
#include "StatComponent_Gunner.h"

#include "EnemyCharacter_Gunner.generated.h"

/**
 * 
 */



DECLARE_MULTICAST_DELEGATE(FOnHpIsZero);


UCLASS()
class ESCAPEGAME_API AEnemyCharacter_Gunner : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter_Gunner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	


	UFUNCTION(BlueprintCallable)
	void Attack() override;
	UFUNCTION(BlueprintCallable)
	void Reload();
	UFUNCTION(BlueprintCallable)
	void SetADS();
	UFUNCTION(BlueprintCallable)
	void ReleaseADS();
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	
	//False면 left true면 right
	void PlaySFXFoot(bool bResult);
	//state component-> take damage 에서 broadcast 됨
	FOnHpIsZero OnHPIsZeroDelegate;
	//state component-> take damage 에서 broadcast 됨
	FOnHPChangeDelegate OnHpChangedDelegate;

protected:
	
	// ==============================Form AActor=====================
	virtual void BeginPlay() override;
	virtual void BeginDestroy()override;
	virtual void PostInitializeComponents() override;
	
	// Delegate 등록은 자식 클레스에서
		virtual	void SaveGame(class UEGSaveGame* SaveInstance);
	// Delegate 등록은 자식 클레스에서
		virtual	void LoadGame(const class UEGSaveGame* LoadInstance);

	
	void initComponents();
	void loadAssets();
	void playSFXGun();
	
	
	//init ai perception component
	//void setupPerception();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UAudioComponent* SFX_Fire1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UAudioComponent* SFX_Fire2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SFX")
		UAudioComponent* SFX_Foot_L;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SFX")
		UAudioComponent* SFX_Foot_R;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UComponent_Mag* MagComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bCanFire;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		float Cooltime;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		FVector Point_Muzzle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStatComponent_Gunner* StatComponent;
	UPROPERTY()
		class UAnimInstance_Gunner* Anim;
	


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	//	class UAISenseConfig_Sight * AiConfigSight;


};
