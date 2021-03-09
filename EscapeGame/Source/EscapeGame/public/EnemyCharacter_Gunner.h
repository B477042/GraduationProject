// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EnemyCharacter.h"
#include "Component_Mag.h"
#include "Components/AudioComponent.h"
#include "StateComponent_Gunner.h"

#include "EnemyCharacter_Gunner.generated.h"

/**
 * 
 */




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
	void playGunSFX();
	//init ai perception component
	//void setupPerception();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UAudioComponent* FireSound1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UAudioComponent* FireSound2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UComponent_Mag* MagComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bCanFire;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		float Cooltime;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		FVector Point_Muzzle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStateComponent_Gunner* StateComponent;
	UPROPERTY()
		class UAnimInstance_Gunner* Anim;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	//	class UAISenseConfig_Sight * AiConfigSight;


};
