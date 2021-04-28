// Fill out your copyright notice in the Description page of Project Settings.


#include "StateComponent_Gunner.h"
#include "EnemyCharacter_Gunner.h"

UStateComponent_Gunner::UStateComponent_Gunner()
{
	State = EGunnerState::E_Idle;

	JogSpeed = 300.0f;
	ADSSpeed = 150.0f;
	Hp = 110.0f;
}
void UStateComponent_Gunner::BeginPlay()
{

	Super::BeginPlay();

	SetState(EGunnerState::E_Idle);
}


void UStateComponent_Gunner::SetState(EGunnerState NewState)
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

EGunnerState UStateComponent_Gunner::GetState()
{
	return State;
}

void UStateComponent_Gunner::SaveGame(FEnemyData& SaveData)
{
	/*if (!SaveData)
	{
		EGLOG(Error, TEXT("SaveData is nullptr"));
		return;
	}*/
	SaveData.Hp = Hp;
	
	


}

void UStateComponent_Gunner::LoadGame(const FEnemyData& LoadData)
{
	
	/*if (!LoadData)
	{
		EGLOG(Error, TEXT("LoadData is nullptr"));
		return;
	}*/
	Hp = LoadData.Hp;


}

void UStateComponent_Gunner::TakeDamage(float Damage)
{
	Hp -= Damage;
	if (Hp <= 0)
		NotifyDeath();
}

void UStateComponent_Gunner::NotifyDeath()
{

}