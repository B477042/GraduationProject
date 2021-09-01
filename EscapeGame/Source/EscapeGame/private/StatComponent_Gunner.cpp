// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_Gunner.h"
#include "EnemyCharacter_Gunner.h"
#include "GameFramework/CharacterMovementComponent.h"

UStatComponent_Gunner::UStatComponent_Gunner()
{
	State = EGunnerState::E_Idle;

	JogSpeed = 300.0f;
	ADSSpeed = 150.0f;
	CurrentHP = DefaultHp;
	MaxHP = DefaultHp;
	DropExp = 100;
}
void UStatComponent_Gunner::BeginPlay()
{

	Super::BeginPlay();

	SetState(EGunnerState::E_Idle);
}


void UStatComponent_Gunner::SetState(EGunnerState NewState)
{
	State = NewState;

	auto Character =Cast<AEnemyCharacter_Gunner>( GetOwner());

	if (!Character)return;

	switch (State)
	{
	case EGunnerState::E_Idle:
		Character->GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
		break;
	case EGunnerState::E_ADS:
		Character->GetCharacterMovement()->MaxWalkSpeed = ADSSpeed;
		break;
	case EGunnerState::E_Attack:
		
		break;
	case EGunnerState::E_Crouch:
		Character->GetCharacterMovement()->MaxWalkSpeed = ADSSpeed;
		break;
	}


}

EGunnerState UStatComponent_Gunner::GetState()
{
	return State;
}

void UStatComponent_Gunner::SaveGame(FEnemyData* SaveData)
{
	/*if (!SaveData)
	{
		EGLOG(Error, TEXT("SaveData is nullptr"));
		return;
	}*/
	Super::SaveGame(SaveData);
	
	


}

void UStatComponent_Gunner::LoadGame(const FEnemyData* LoadData)
{
	Super::LoadGame(LoadData);
	/*if (!LoadData)
	{
		EGLOG(Error, TEXT("LoadData is nullptr"));
		return;
	}*/
	


}

void UStatComponent_Gunner::TakeDamage(float Damage)
{
	
	AEnemyCharacter_Gunner* OwnerChara = Cast<AEnemyCharacter_Gunner>(GetOwner());
	if (!OwnerChara)return;

	CurrentHP -= Damage;
	OwnerChara->OnHpChangedDelegate.Broadcast();

	if (CurrentHP <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("%s Died"), *OwnerChara->GetName());
		OwnerChara->OnHPIsZeroDelegate.Broadcast();
	}
}

