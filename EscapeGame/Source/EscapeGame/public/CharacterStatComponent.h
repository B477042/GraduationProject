// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "CharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangeDelegate);

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	void TestLogic();

	//int32 GetDropExp()const;
	float GetAttack()const;
	float GetHPRatio()const;
	

	FOnHPChangeDelegate HPChagnDelegate;
private:
	const float MaxHP=100.0f;
	float timer;
private:
	
	//save current HP,Transient ����
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentHP;
	UPROPERTY(isibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float CurrentATK;
};
