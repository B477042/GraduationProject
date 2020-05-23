// Fill out your copyright notice in the Description page of Project Settings.

#include "StatComponent.h"
#include "EGPlayerCharacter.h"
#include "EnemyCharacter.h"
//#include "..\public\CharacterStatComponent.h"




// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//CurrentHP = MaxHP;
	CurrentATK = 10.0f;

	bIsAttacking = false;
	
	//EGLOG(Warning, TEXT("Stat component!"));
	// ...
}


void UStatComponent::InitializeComponent()
{
	EGLOG(Warning, TEXT("Stat component initialize"));
	Super::InitializeComponent();
}

// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetWalking();
	// ...
	
}




// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//BasicDamage();
	// ...
}

// TakeDamage Frame
void UStatComponent::TakeDamage(float NewDamage)
{
	if (NewDamage < 0)
	{
		EGLOG(Warning, TEXT("Minors Number Input in Take Damage!"));
		return;
	}
	CurrentHP -= NewDamage;
	if(!IsDead())
	HPChangedDelegate.Broadcast();
}

//Set a point 
void UStatComponent::SetHP(float NewHP)
{
	//EGLOG(Warning, TEXT("HP : %f"), GetHPRatio());
	CurrentHP = NewHP;
	if (!IsDead())
	HPChangedDelegate.Broadcast();
}

//Plus(Heal) HP
void UStatComponent::HealHP(float AddHP)
{
	if (AddHP < 0)
	{
		EGLOG(Warning, TEXT("Minors Number Input in Heal HP!"));
		return;
	}

	CurrentHP += AddHP;
	if (CurrentHP > MaxHP)
		CurrentHP = MaxHP;

	HPChangedDelegate.Broadcast();

}



void UStatComponent::OnAttacking(bool bResult)
{
	bIsAttacking = bResult;
}


void UStatComponent::SetDontMove()
{
	auto Character = Cast<ACharacter>(GetOwner());
	if (Character != nullptr)
	{
		auto Movement = Character->GetCharacterMovement();
		Movement->MaxWalkSpeed = MinWalkingSpeed;
	}

}

void UStatComponent::SetRunning()
{
	auto Character = Cast<ACharacter>(GetOwner());
	if (Character != nullptr)
	{
		auto Movement = Character->GetCharacterMovement();
		Movement->MaxWalkSpeed = MaxRunningSpeed;
	}
}

void UStatComponent::SetWalking()
{
	auto Character = Cast<ACharacter>(GetOwner());
	if (Character != nullptr)
	{
		auto Movement = Character->GetCharacterMovement();
		Movement->MaxWalkSpeed = MaxWalkingSpeed;
	}
}
// return True If dead
bool UStatComponent::IsDead()
{
	if (CurrentHP > 0)return false;
	CurrentHP = 0.0f;
	EGLOG(Error, TEXT("He is Dead"));
	
	HPChangedDelegate.Broadcast();
	HPZeroDelegate.Broadcast();
	return true;
}

void UStatComponent::SetSpeedLimits(const float & maxWalk, const float & minWalk, const float & maxRunning)
{
	MaxWalkingSpeed = maxWalk;
	MinWalkingSpeed = minWalk;
	MaxRunningSpeed = maxRunning;
}




float UStatComponent::GetATK() const
{
	return CurrentATK;
}

float UStatComponent::GetHPRatio() const
{
	return (CurrentHP<0.0f)? 0.0f : CurrentHP/MaxHP;
}

float UStatComponent::GetHP() const
{
	return CurrentHP;
}



bool UStatComponent::IsAttacking() const
{
	return bIsAttacking;
}

//void UStatComponent::LoadDBfromOwner( const float & maxWalk, const float & minWalk, const float & maxRunning)
//{
//
//	MaxWalkingSpeed = maxWalk;
//	MinWalkingSpeed = minWalk;
//	MaxRunningSpeed = maxRunning;
//}


