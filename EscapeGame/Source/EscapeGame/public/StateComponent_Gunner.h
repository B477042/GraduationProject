// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "StateComponent.h"
#include "EGSaveGame.h"
#include "StateComponent_Gunner.generated.h"

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
class ESCAPEGAME_API UStateComponent_Gunner : public UActorComponent
{
	GENERATED_BODY()

public:
	UStateComponent_Gunner();
protected:
	virtual void BeginPlay()override;
public:
	void SetState(EGunnerState NewState);
	EGunnerState GetState();

	void SaveGame(FEnemyData* SaveData);
	void LoadGame(const FEnemyData* LoadData);

	void TakeDamage(float Damage);
	void NotifyDeath();

	

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		EGunnerState State;
	UPROPERTY(Transient, EditInstanceOnly, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
		float JogSpeed;
	UPROPERTY(Transient, EditInstanceOnly, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
		float ADSSpeed;
	UPROPERTY(Transient, EditInstanceOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float Hp;

};
