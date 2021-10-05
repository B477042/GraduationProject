// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StatComponent.h"

#include "StatComponent_Player.generated.h"

/**
 * Stat Component For Player Actor
 * Add Additional Stat
 * Add Combo Condition
 */
//
DECLARE_DELEGATE(FOnExpChanged);
DECLARE_DELEGATE(FOnLevelUP);

UCLASS()
class ESCAPEGAME_API UStatComponent_Player : public UStatComponent
{
	GENERATED_BODY()
public:
	UStatComponent_Player();

	virtual void InitializeComponent()override;
	virtual void BeginDestroy()override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void TakeDamage(float NewDamage)override;
	bool CheckCanComboAttack()const;
	bool CheckCanChargeAttack()const;
	
	int32 GetMaxCombo()const;
	int32 GetCurrentCombo()const;

	void SetComboAttackInput(bool bResult);
	void SetChargeAttackInput(bool bResult);
	void SetComboStartState();
	void SetComboEndState();

	int32 GetLevel();
	//return exp
	float GetExp();
	float GetExpRatio();
	
	void AddCombo(int32 Amount);
	void ResetCombo();
	
	//Get Exp form enemy's Drop Exp
	UFUNCTION(BlueprintCallable)
	void GainExp(const int32 &DropExp );


	FOnExpChanged OnExpChanged;
	FOnLevelUP OnLevelUP;
	//virtual  void LoadDataTable()override ;

	void LoadGameStat(int32 newLevel, float newExp, float newHp);
	
private:
	//Called when Exp is enough to level up
	void LevelUp();
	//data table���� level�� �´� data�� �����´�
	void LoadLevelData();

	
private:

	

	UPROPERTY(VisibleInstanceOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		int32 MaxCombo;


	//Player level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 Level;
	//Player's Current Exp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 Exp;
	//Exp, need to level up
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 NextExp;
	//Size of Inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 ItemSlot;

	//Normal Combo�� ������ �Է��� �Է� �ƴ���
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bIsComboAttackInputOn;
	//Charge Combo�� ������ �Է��� �Է� �ƴ���
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bIsChargeAttackInputOn;
	//Can next Combo attack
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bCanComboAttack;
	//Can next Charge Attack
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bCanChargeAttack;
	
	UPROPERTY(VisibleAnywhere, Category = "Effect")
		USoundWave* SFX_LevelUp;
	UPROPERTY(VisibleAnywhere, Category = "Effect")
		class UParticleSystem* VFX_LevelUp;

	/*UPROPERTY( VisibleInstanceOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
		FPlayerTableRow* PlayerTableRow;*/
	//UPROPERTY(Transient, VisibleInstanceOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	//	UDataTable* PlayerTable;
};
