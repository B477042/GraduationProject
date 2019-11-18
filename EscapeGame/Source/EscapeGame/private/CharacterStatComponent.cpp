// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterStatComponent.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHP = MaxHP;
	CurrentATK = 10.0f;
	timer = 0.0f;
	// ...
}


void UCharacterStatComponent::InitializeComponent()
{
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
	TestLogic();
	// ...
}

void UCharacterStatComponent::SetDamage(float NewDamage)
{
	CurrentHP -= NewDamage;
}

void UCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
}

void UCharacterStatComponent::TestLogic()
{
	timer += GetWorld()->DeltaTimeSeconds;
	if (timer > 1.0f)
	{
		SetDamage(5.0f);
		timer = 0.0f;
	}
}


float UCharacterStatComponent::GetAttack() const
{
	return CurrentATK;
}

float UCharacterStatComponent::GetHPRatio() const
{
	return (CurrentHP<0.0f)? 0.0f : CurrentHP/MaxHP;
}

