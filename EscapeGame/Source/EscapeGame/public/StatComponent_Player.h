// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StatComponent.h"
#include "StatComponent_Player.generated.h"

/**
 * Stat Component For Player Actor
 * Add Additional Stat
 * Add Combo Condition
 */
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
	void SetComboEndState();
	void SetComboStartState();

	void AddCombo(int32 Amount);
	void ResetCombo();



private:

	UPROPERTY(VisibleInstanceOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		int32 MaxCombo;

	//Normal Combo를 진행할 입력이 입력 됐는지
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bIsComboAttackInputOn;
	//Charge Combo를 진행할 입력이 입력 됐는지
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bIsChargeAttackInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bCanComboAttack;//Can next Combo attack
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bCanChargeAttack;//Can next Charge Attack
	
};
