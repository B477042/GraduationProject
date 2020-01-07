﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FIsHPZero);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatComponent();

	virtual void InitializeComponent()override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//virtual void PostInitializeComponent();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TakeDamage(float NewDamage);
	//set new hp. 
	void SetHP(float NewHP);
	//Add HP to Current HP
	void HealHP(float AddHP);
	void AddCombo(int count);
	void ResetCombo();
	void BasicDamage();
	void OnAttacking(bool bResult);
	
	

	//int32 GetDropExp()const;
	float GetAttackPoint()const;
	float GetHPRatio()const;
	float GetHP()const;
	float GetCurrentCombo()const;
	bool IsAttacking()const;
	

	FOnHPChangeDelegate HPChangedDelegate;
	FIsHPZero HPZeroDelegate;
private:
	const float MaxHP=100.0f;
	float timer;
private:
	
	//save current HP,
	//Transient 이 프로퍼티는 휘발성이라, 저장 또는 로드되지 않습니다. 
	//이런 식의 지정자가 붙은 프로퍼티는 로드 시간에 0 으로 채워집니다.
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentATK;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		int CurrentCombo;
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool	bIsAttacking;

};
