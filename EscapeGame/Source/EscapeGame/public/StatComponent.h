// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FIsHPZero);


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
	
	void TakeDamage(float NewDamage);
	//set new hp. 
	void SetHP(float NewHP);

	//Add HP to Current HP
	void HealHP(float AddHP);
	
	//void BasicDamage();//자신이 초당 입는 기본 데미지
	void OnAttacking( bool bResult);

	
	void SetDontMove();
	void SetFreeMove();
	void SetRunning();
	void SetWalking();
	

	void SetSpeedLimits(const float&maxWalk, const float&minWalk, const float&maxRunning);
	//Load Movement Data form owner's static data
	//void LoadDBfromOwner(const float&maxWalk, const float&minWalk, const float&maxRunning);


	//int32 GetDropExp()const;
	

	float GetATK()const;
	float GetHPRatio()const;
	float GetHP()const;
	
	bool IsAttacking()const;
	//PURE_VIRTUAL( 함수 이름, 기본 리턴 값;)
	//virtual void LoadDataTable() PURE_VIRTUAL(StatComponent::LoadDataTable, ;);

	FOnHPChangeDelegate HPChangedDelegate;
	FIsHPZero HPZeroDelegate;

protected:
	/*const float MaxHP=100.0f;
	const float MaxWalkingSpeed = 500.0f;
	const float MaxRunningSpeed = 1000.0f;
	const float MinWalkingSpeed = 1.0f;*/
	float MaxHP ;
	float MaxWalkingSpeed ;
	float MaxRunningSpeed ;
	float MinWalkingSpeed ;
	//float timer;
	

protected:
	
	//save current HP,
	//Transient 이 프로퍼티는 휘발성이라, 저장 또는 로드되지 않습니다. 
	//이런 식의 지정자가 붙은 프로퍼티는 로드 시간에 0 으로 채워집니다.
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;
	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentATK;


	UPROPERTY( VisibleInstanceOnly,BlueprintReadOnly ,Category = Attacking, Meta = (AllowPrivateAccess = true))
		bool bIsAttacking;



};
