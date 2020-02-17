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

	// ...
	
}




// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	BasicDamage();
	// ...
}

// TakeDamage Frame
void UStatComponent::TakeDamage(float NewDamage)
{
	
	CurrentHP -= NewDamage;
	HPChangedDelegate.Broadcast();
}

//Set a point 
void UStatComponent::SetHP(float NewHP)
{
	//EGLOG(Warning, TEXT("HP : %f"), GetHPRatio());
	CurrentHP = NewHP;
	HPChangedDelegate.Broadcast();
}

//Plus(Heal) HP
void UStatComponent::HealHP(float AddHP)
{
	CurrentHP += AddHP;
	if (CurrentHP > MaxHP)
		CurrentHP = MaxHP;

	HPChangedDelegate.Broadcast();
}

void UStatComponent::AddCombo(int32 Amount)
{
	CurrentCombo += Amount;
}



void UStatComponent::ResetCombo()
{
	CurrentCombo = 0;
}

void UStatComponent::BasicDamage()
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

void UStatComponent::OnAttacking(bool bResult)
{
	bIsAttacking = bResult;
}

void UStatComponent::SetComboAttackInput(bool bResult)
{
	//bCanComboAttack = bResult;
	bIsComboAttackInputOn = bResult;
	//bIsChargeAttackInputOn = false;
//	EGLOG(Warning, TEXT("Set Combo Input : %d"), bIsComboAttackInputOn);
}

void UStatComponent::SetChargeAttackInput(bool bResult)
{
	//bCanChargeAttack = bResult;
	bIsChargeAttackInputOn = bResult;
//	EGLOG(Warning, TEXT("Set ChargeAttack Input : %d"), bIsChargeAttackInputOn);
	//bIsComboAttackInputOn = false;
}
//montage paly�� ����Ǹ� ȣ�� �� ���̴�
void UStatComponent::SetComboEndState()
{
	bCanComboAttack = false;
	bCanChargeAttack = false;
	bIsAttacking = false;
	//������ �Ұ����ϰ� ���ش�
	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;
	ResetCombo();

	SetFreeMove();
}

//Montage Play�� ���۵Ǹ� ȣ��� ���´�
void UStatComponent::SetComboStartState()
{
	
	bCanChargeAttack = true;
	bCanComboAttack = true;
	bIsAttacking = true;
	AddCombo(1);
	////������ ���� ������ ���� �Է��� �ʱ�ȭ ��Ų��
	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;

	SetDontMove();
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

void UStatComponent::SetFreeMove()
{
	//Set Player's Character Movement To Normal
	auto Character = Cast<AEGPlayerCharacter>(GetOwner());
	if (Character != nullptr)
	{
		auto Movement = Character->GetCharacterMovement();
		Movement->MaxWalkSpeed = MaxWalkingSpeed;
		return;
	}

}

void UStatComponent::SetRunning()
{
	auto Character = Cast<AEGPlayerCharacter>(GetOwner());
	if (Character != nullptr)
	{
		auto Movement = Character->GetCharacterMovement();
		Movement->MaxWalkSpeed = MaxRunningSpeed;
	}
}

void UStatComponent::SetWalking()
{
	auto Character = Cast<AEGPlayerCharacter>(GetOwner());
	if (Character != nullptr)
	{
		auto Movement = Character->GetCharacterMovement();
		Movement->MaxWalkSpeed = MinWalkingSpeed;
	}
}




float UStatComponent::GetAttackPoint() const
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

int32 UStatComponent::GetMaxCombo() const
{
	return MaxCombo;
}

int32 UStatComponent::GetCurrentCombo() const
{
	return  CurrentCombo;
}


bool UStatComponent::IsAttacking() const
{
	return bIsAttacking;
}

bool UStatComponent::CheckCanComboAttack() const
{
	return bIsComboAttackInputOn;
}

bool UStatComponent::CheckCanChargeAttack() const
{
	return bIsChargeAttackInputOn;
}

void UStatComponent::LoadDBfromOwner(const float & hp, const float & maxWalk, const float & minWalk, const float & maxRunning)
{
	MaxHP = hp;
	MaxWalkingSpeed = maxWalk;
	MinWalkingSpeed = minWalk;
	MaxRunningSpeed = maxRunning;
}


