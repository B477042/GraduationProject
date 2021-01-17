// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "EnemyCharacter.h"
#include "Components/AudioComponent.h"
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
	
protected:
	
	// ==============================Form AActor=====================
	virtual void BeginPlay() override;
	virtual void BeginDestroy()override;
	virtual void PostInitializeComponents() override;
	
	//Save Game 단계에서Enemy Character들이 공통적으로 저장할 정보를 저장한다. Delegate 등록은 자식 클레스에서
		virtual	void SaveGame(class UEGSaveGame* SaveInstance);
	//Load Game 단계에서 Enemmy Character들이 공통적으로 저장할 정보를 저장한다. Delegate 등록은 자식 클레스에서
		virtual	void LoadGame(const class UEGSaveGame* LoadInstance);


	void initComponents();
	void loadAssets();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UAudioComponent* FireSound1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UAudioComponent* FireSound2;
};
