// Fill out your copyright notice in the Description page of Project Settings.

#include "StatComponent.h"
#include "EGPlayerCharacter.h"
#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"




// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//CurrentHP = MaxHP;
	CurrentATK = 10.0f;

	bIsAttacking = false;
	bIsDamageable = true;
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


	if (bIsDamageable)
	{
		CurrentHP -= NewDamage;
		EGLOG(Log, TEXT("%s Take damage! amount : %f"), *GetOwner()->GetName(), NewDamage);
		if (NewDamage >= 10.0f)
		{
			auto player = Cast<AEGPlayerCharacter>(GetOwner());
			if (player)
			{
				player->OnTakeHugeDamageDelegate.Broadcast();
			}


			
		}

	}

	//Check is hp under 0?
	//If so, Broadcast Dead Delegate
	if (!IsDead())
	{
		HPChangedDelegate.Broadcast();
	}
}

//Set a point 
void UStatComponent::SetHP(float NewHP)
{
	//EGLOG(Warning, TEXT("HP : %f"), GetHPRatio());
	CurrentHP = NewHP;
	if (CurrentHP > MaxHP)MaxHP = CurrentHP;
	if (!IsDead())
	HPChangedDelegate.Broadcast();
}
// return True If dead
bool UStatComponent::IsDead()
{
	if (CurrentHP > 0)return false;



	//Delegate Call once
	if (bIsDamageable)
	{
		CurrentHP = 0.0f;
		HPChangedDelegate.Broadcast();
		HPZeroDelegate.Broadcast();
		bIsDamageable = false;
		EGLOG(Log, TEXT("%s is Dead"), *GetOwner()->GetName());
		return true;
	}

	EGLOG(Log, TEXT("%s is already dead"), *GetOwner()->GetName());

	return true;
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
		//Movement->JumpZVelocity = 0.0f;
	}

}

void UStatComponent::SetRunning()
{
	auto Character = Cast<ACharacter>(GetOwner());
	if (Character != nullptr)
	{
		//공격중이면 뛰지 못하게
		if (bIsAttacking)return;
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



bool UStatComponent::GetIsDamageable() const
{
	return bIsDamageable;
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


