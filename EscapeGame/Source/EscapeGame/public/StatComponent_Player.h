// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StatComponent.h"

#include "StatComponent_Player.generated.h"

/**
 * Stat Component For Player Actor
 * Add Additional Stat
 * Add Combo Condition
 */
DECLARE_MULTICAST_DELEGATE(FStaminaChangedDelegate);

UCLASS()
class ESCAPEGAME_API UStatComponent_Player : public UStatComponent
{
	GENERATED_BODY()
public:
	UStatComponent_Player();

	virtual void InitializeComponent()override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CheckCanComboAttack()const;
	bool CheckCanChargeAttack()const;
	
	int32 GetMaxCombo()const;
	int32 GetCurrentCombo()const;

	void SetComboAttackInput(bool bResult);
	void SetChargeAttackInput(bool bResult);
	void SetComboStartState();
	void SetComboEndState();
	//===========
	//Stamina관련
	//============
	void UseStamina(float DeltaTime);
	//void SetRunning();
	bool SetStaminaUsing(bool bResult);
	bool CanUsingStamina();

	float GetStamina();
	float GetStaminaRatio();
	
	void AddCombo(int32 Amount);
	void ResetCombo();
	
	//Get Exp form enemy's Drop Exp
	UFUNCTION(BlueprintCallable)
	void GetExp(const int32 &DropExp );

	FStaminaChangedDelegate StaminaChangedDelegate;
	//virtual  void LoadDataTable()override ;

	
private:
	//Called when Exp is enough to level up
	void levelUp();
	//data table에서 level에 맞는 data를 가져온다
	void loadLevelData();

	void RecoverStamina(float DeltaTime);

	const float MaxStamina = 100.0f;
	float TimerStamina;
private:

	

	UPROPERTY(VisibleInstanceOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		int32 MaxCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		float Stamina;
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

	//Normal Combo를 진행할 입력이 입력 됐는지
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bIsComboAttackInputOn;
	//Charge Combo를 진행할 입력이 입력 됐는지
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bIsChargeAttackInputOn;
	//Can next Combo attack
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bCanComboAttack;
	//Can next Charge Attack
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bCanChargeAttack;
	//현재 Stamina가 사용되고 있는지 체크를 한다
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		bool bIsStaminaUsing;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		bool bCanUsingStamina;



	/*UPROPERTY( VisibleInstanceOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
		FPlayerTableRow* PlayerTableRow;*/
	//UPROPERTY(Transient, VisibleInstanceOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	//	UDataTable* PlayerTable;
};
