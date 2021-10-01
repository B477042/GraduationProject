// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"

#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FIsHPZero);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageOcureDelegate,void);


/*
	Define Character's Stat. Such as HP, ATK, Stamina, Combo, etc...

*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatComponent();

	virtual void InitializeComponent()override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(float NewDamage);
	//set new hp. 
	void SetHP(float NewHP);
	void SetMaxHP(float NewHP) { MaxHP = NewHP; }
	//Add HP to Current HP
	void HealHP(float AddHP);

	//void BasicDamage();//자신이 초당 입는 기본 데미지
	void OnAttacking(bool bResult);

	//Set Actor Can't Move Around using MinWalkingSpeed
	void SetDontMove();

	//Set Actor Speed To MaxRunningSpeed
	void SetRunning();
	//Set Actor Speed To MaxWalingSpeed
	void SetWalking();
	

	void SetSpeedLimits(const float&maxWalk, const float&minWalk, const float&maxRunning);
	//Load Movement Data form owner's static data
	//void LoadDBfromOwner(const float&maxWalk, const float&minWalk, const float&maxRunning);
	void SetDamageable(bool bResult) { bIsDamageable = bResult; }

	//int32 GetDropExp()const;


	float GetATK()const;
	UFUNCTION(BlueprintCallable)
	float GetHPRatio()const;
	UFUNCTION(BlueprintCallable)
	float GetMaxHP()
	{return MaxHP;}
	UFUNCTION(BlueprintCallable)
	float GetHP()const;
	
	bool GetIsDamageable()const;
	bool IsAttacking()const;
	//PURE_VIRTUAL( 함수 이름, 기본 리턴 값;)
	//virtual void LoadDataTable() PURE_VIRTUAL(StatComponent::LoadDataTable, ;);

	FOnHPChangeDelegate HPChangedDelegate;
	//UPROPERTY(BlueprintAssignable)
	FIsHPZero HPZeroDelegate;

protected:
	/*const float MaxHP=100.0f;
	const float MaxWalkingSpeed = 500.0f;
	const float MaxRunningSpeed = 1000.0f;
	const float MinWalkingSpeed = 1.0f;*/
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	float MaxHP ;
	float MaxWalkingSpeed ;
	float MaxRunningSpeed ;
	float MinWalkingSpeed ;
	//float timer;
	//Check Hp is under 0
	UFUNCTION(BlueprintCallable)
	virtual bool IsDead();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bIsDamageable;

protected:
	
	//save current HP,
	//Transient 이 프로퍼티는 휘발성이라, 저장 또는 로드되지 않습니다. 
	//이런 식의 지정자가 붙은 프로퍼티는 로드 시간에 0 으로 채워집니다.
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		float CurrentHP;
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentATK;


	UPROPERTY( VisibleInstanceOnly,BlueprintReadOnly ,Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bIsAttacking;



};
