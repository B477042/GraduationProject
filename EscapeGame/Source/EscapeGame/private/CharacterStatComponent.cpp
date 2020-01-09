// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterStatComponent.h"
#include "..\public\CharacterStatComponent.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHP = MaxHP;
	CurrentATK = 10.0f;
	timer = 0.0f;
	bIsAttacking = false;
	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;
	bCanChargeAttack = false;
	bCanComboAttack = false;
	CurrentCombo = 0;
	MaxCombo = 4;
	EGLOG(Warning, TEXT("Stat component!"));
	// ...
}


void UCharacterStatComponent::InitializeComponent()
{
	EGLOG(Warning, TEXT("Stat component initialize"));
	Super::InitializeComponent();
}

// Called when the game starts
void UCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




// Called every frame
void UCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	BasicDamage();
	// ...
}

// TakeDamage Frame
void UCharacterStatComponent::TakeDamage(float NewDamage)
{
	
	CurrentHP -= NewDamage;
	HPChangedDelegate.Broadcast();
}

//Set a point 
void UCharacterStatComponent::SetHP(float NewHP)
{
	//EGLOG(Warning, TEXT("HP : %f"), GetHPRatio());
	CurrentHP = NewHP;
	HPChangedDelegate.Broadcast();
}

//Plus(Heal) HP
void UCharacterStatComponent::HealHP(float AddHP)
{
	CurrentHP += AddHP;
	if (CurrentHP > MaxHP)
		CurrentHP = MaxHP;

	HPChangedDelegate.Broadcast();
}

void UCharacterStatComponent::AddCombo(int32 Amount)
{
	CurrentCombo += Amount;
}



void UCharacterStatComponent::ResetCombo()
{
	CurrentCombo = 0;
}

void UCharacterStatComponent::BasicDamage()
{
	timer += GetWorld()->DeltaTimeSeconds;
	
	if (timer > 1.0f)
	{
		TakeDamage(1.0f);
		timer = 0.0f;
	}
	if (CurrentHP < 0.0f)
		SetHP(0.0f);
}

void UCharacterStatComponent::OnAttacking(bool bResult)
{
	bIsAttacking = bResult;
}

void UCharacterStatComponent::SetCanNextNA(bool bResult)
{
	bCanComboAttack = bResult;
}

void UCharacterStatComponent::SetCanNextCA(bool bResult)
{
	bCanChargeAttack = bResult;
}
//montage paly가 종료되면 호출 될 것이다
void UCharacterStatComponent::SetComboEndState()
{
	bCanComboAttack = false;
	bCanChargeAttack = false;
	bIsAttacking = false;

	ResetCombo();

}

void UCharacterStatComponent::SetComboStartState()
{
	AddCombo(1);
	bCanChargeAttack = true;
	bCanComboAttack = true;

	
}




float UCharacterStatComponent::GetAttackPoint() const
{
	return CurrentATK;
}

float UCharacterStatComponent::GetHPRatio() const
{
	return (CurrentHP<0.0f)? 0.0f : CurrentHP/MaxHP;
}

float UCharacterStatComponent::GetHP() const
{
	return CurrentHP;
}

int32 UCharacterStatComponent::GetMaxCombo() const
{
	return MaxCombo;
}

int32 UCharacterStatComponent::GetCurrentCombo() const
{
	return  CurrentCombo;
}


bool UCharacterStatComponent::IsAttacking() const
{
	return bIsAttacking;
}

bool UCharacterStatComponent::CheackCanComboAttack() const
{
	return bCanComboAttack;
}

bool UCharacterStatComponent::CheackCanChargeAttack() const
{
	return bCanChargeAttack;
}


