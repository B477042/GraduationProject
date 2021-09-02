// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "StatComponent_Enemy.h"
#include "EGSaveGame.h"
#include "StatComponent_Gunner.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGunnerState : uint8
{
	E_Idle UMETA(DisplayName = Idle),
	E_ADS UMETA(DisplayName = ADS),
	E_Attack UMETA(DisplayName = Attack),
	E_Crouch UMETA(DisplayName = Crouch)
	
};




UCLASS()
class ESCAPEGAME_API UStatComponent_Gunner : public UStatComponent_Enemy
{
	GENERATED_BODY()

public:
	UStatComponent_Gunner();
protected:
	virtual void BeginPlay()override;
public:
	void SetState(EGunnerState NewState);
	EGunnerState GetState();

	virtual void SaveGame(FEnemyData* SaveData)override;
	
	virtual void LoadGame(const FEnemyData* LoadData)override;

	virtual void TakeDamage(float Damage)override;
	
	


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		EGunnerState State;
	UPROPERTY(Transient, EditInstanceOnly, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
		float JogSpeed;
	UPROPERTY(Transient, EditInstanceOnly, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
		float ADSSpeed;
	

	const float DefaultHp = 110.0f;
};
