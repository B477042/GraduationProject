// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_Player.h"
#include "EGPlayerController.h"
#include "DT_DataStruct.h"
#include "EGGameInstance.h"
#include "EGPostProcessVolume.h"


UStatComponent_Player::UStatComponent_Player()
{

	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;
	bCanChargeAttack = false;
	bCanComboAttack = false;
	CurrentCombo = 0;
	MaxCombo = 4;

	Level = 1;

	MinWalkingSpeed = 0.0f;
	MaxWalkingSpeed = 600.0f;
	MaxRunningSpeed = 1000.0f;
	Stamina = 0.0f;
	TimerStamina = 0.0f;
	bIsStaminaUsing = false;
	bCanUsingStamina = true;
}

void UStatComponent_Player::InitializeComponent()
{
	Super::InitializeComponent();
}

void UStatComponent_Player::BeginPlay()
{
	Super::BeginPlay();
	loadLevelData();
}



void UStatComponent_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//EGLOG(Warning, TEXT("Player Stat Tick"));
	//Tick이 켜진 컴포넌트인 것 확인 됨
	RecoverStamina(DeltaTime);

}

void UStatComponent_Player::TakeDamage(float NewDamage)
{
	Super::TakeDamage(NewDamage);

	


}

bool UStatComponent_Player::CheckCanComboAttack() const
{
	return bIsComboAttackInputOn;
}

bool UStatComponent_Player::CheckCanChargeAttack() const
{
	return bIsChargeAttackInputOn;
}

int32 UStatComponent_Player::GetMaxCombo() const
{
	return MaxCombo;
}

int32 UStatComponent_Player::GetCurrentCombo() const
{
	return CurrentCombo;
}

void UStatComponent_Player::SetComboAttackInput(bool bResult)
{
	bIsComboAttackInputOn = bResult;
}

void UStatComponent_Player::SetChargeAttackInput(bool bResult)
{
	bIsChargeAttackInputOn = bResult;
}

void UStatComponent_Player::SetComboStartState()
{
	bCanChargeAttack = true;
	bCanComboAttack = true;
	bIsAttacking = true;
	bCanUsingStamina = false;
	AddCombo(1);
	////������ ���� ������ ���� �Է��� �ʱ�ȭ ��Ų��
	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;

	SetDontMove();
}

void UStatComponent_Player::SetComboEndState()
{

	bCanComboAttack = false;
	bCanChargeAttack = false;
	bIsAttacking = false;
	bCanUsingStamina = true;
	//������ �Ұ����ϰ� ���ش�
	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;
	ResetCombo();

	SetWalking();
}
void UStatComponent_Player::UseStamina(float DeltaTime)
{
	if (!bCanUsingStamina)
	{
		//EGLOG(Warning, TEXT("Can't use Stamina"));
		return;
	}
	//if (!bIsStaminaUsing)SetStaminaUsing(true);
	if (Stamina == 0.0f)
	{
		bIsStaminaUsing = false;
		return;
	}
	if (Stamina < 0.0f)
	{
		bIsStaminaUsing = false;
		Stamina = 0.0f;
		return;
	}
	Stamina -= DeltaTime * 100.0f;
	StaminaChangedDelegate.Broadcast();
}

////Call when Running Start
//void UStatComponent_Player::SetRunning()
//{
//	if (!bCanUsingStamina)return;
//	//if (!GetWorld())return;
//
//
//	//켜준다
//	bIsStaminaUsing = true;
//	/*float DeltaTime = GetWorld()->GetDeltaSeconds();
//	UseStamina(DeltaTime);*/
//	
//
//}
/*
	will Call in Tick
*/
void UStatComponent_Player::RecoverStamina(float DeltaTime)
{
	if (bIsStaminaUsing)
		return;
	if (Stamina > MaxStamina)
	{
		Stamina = MaxStamina;
		return;
	}
		
	if (Stamina == MaxStamina)
	{
		//EGLOG(Warning, TEXT("Stamina is full"));
		StaminaChangedDelegate.Broadcast();
		return;
	}

	//EGLOG(Warning, TEXT("Time Added"));
	TimerStamina += DeltaTime;

	//만약 stamina를 다 써버렸다면
	if (Stamina == 0.0f)
	{
		if (TimerStamina < 3.0f)return;
		bCanUsingStamina = false;
		TimerStamina = 0.0f;
		Stamina += 1.0f;
	}
	/*
		구간별로 스테미너 회복 곡선을 다르게 표현할 것이다
		0~30은 천천히 31~70은 빠르게
		70~100은 천천히 회복되게 할 것이다
	*/
	if (Stamina > 70.0f)
	{
		if (TimerStamina < 0.004f)return;

		TimerStamina = 0.0f;
		Stamina += 0.5f;
		//EGLOG(Warning, TEXT("Stamina Added"));
		StaminaChangedDelegate.Broadcast();
		return;
	}
	else if (Stamina > 30.0f)
	{
		if (TimerStamina < 0.002f)return;
		TimerStamina = 0.0f;
		Stamina += 1.0f;
		bCanUsingStamina = true;
		//EGLOG(Warning, TEXT("Stamina Added"));
		StaminaChangedDelegate.Broadcast();
		return;
	}
	else
	{
		if (TimerStamina < 0.004f)return;
		TimerStamina = 0.0f;
		Stamina += 0.5f;
		//EGLOG(Warning, TEXT("Stamina Added"));
		StaminaChangedDelegate.Broadcast();
		return;
	}
}

bool UStatComponent_Player::SetStaminaUsing(bool bResult)
{
	bIsStaminaUsing = bResult;
	return bIsStaminaUsing;
}

bool UStatComponent_Player::CanUseStamina()
{
	if (Stamina <= 0)
		return false;
	else
		return true;
}

float UStatComponent_Player::GetStamina()
{
	return Stamina;
}

float UStatComponent_Player::GetStaminaRatio()
{
	return (Stamina<0.0f)? 0.0f : Stamina/MaxStamina;
}

int32 UStatComponent_Player::GetLevel()
{
	return Level;
}

float UStatComponent_Player::GetExp()
{
	return Exp;
}


void UStatComponent_Player::AddCombo(int32 Amount)
{
	CurrentCombo += Amount;
}

void UStatComponent_Player::ResetCombo()
{
	CurrentCombo = 0;
}

void UStatComponent_Player::GainExp(const int32 & DropExp)
{
	Exp += DropExp;
	//if Level up
	if (Exp >= NextExp)
	{
		levelUp();
		
	}
}
//
//void UStatComponent_Player::LoadDataTable()
//{
//	/*
//	*	Set Player Table row To DataTable
//	*	if Player Table setted, return
//	*/
//	
//	//if (DataTable == nullptr) { EGLOG(Warning, TEXT("inputted Data Table is nullptr")); return; }
//	
//	//if (PlayerTable != nullptr) { EGLOG(Warning, TEXT("Data Table already loaded")); return; }
//	//PlayerTable = DataTab
//	
//	
//	auto OwnerChara = Cast<ACharacter>(GetOwner());
//	if (OwnerChara == nullptr)
//	{
//		EGLOG(Warning, TEXT("Owner is not Character class"));
//		return;
//	}
//	auto OwnerCon = Cast<AEGPlayerController>(OwnerChara->Controller);
//	if (OwnerCon == nullptr)
//	{
//		EGLOG(Warning, TEXT("Owner controller Casting failed"));
//		return;
//	}
//
//	PlayerTableRow = DataTable->FindRow<FPlayerTableRow>(FName(*(FString::FormatAsNumber(Level))), FString(""));
//}



void UStatComponent_Player::LoadGameStat(int32 newLevel, float newExp, float newHp)
{
	Level = newLevel;
	loadLevelData();
	SetHP( newHp);
	Exp = newExp;

	
	
}

void UStatComponent_Player::levelUp()
{
	//Exp가 NextExp를 초과한 만큼 빼주고
	Exp -= NextExp;
	//0미만이면 Exp를 0으로 설정해준다
	if (Exp < 0)Exp = 0;
	Level++;
	
	loadLevelData();
}

void UStatComponent_Player::loadLevelData()
{

	/*
		
	
	*/
	auto OwnerChara = Cast<ACharacter>(GetOwner());
	if (OwnerChara == nullptr)
	{
		EGLOG(Warning, TEXT("Owner is not Character class"));
		return;
	}
	auto OwnerCon = Cast<AEGPlayerController>(OwnerChara->Controller);
	if (OwnerCon == nullptr)
	{
		EGLOG(Warning, TEXT("Owner controller Casting failed"));
		return;
	}

	auto DataTable = OwnerCon->GetDT_Player();

	FPlayerTableRow* PlayerTableRow;
	PlayerTableRow = DataTable->FindRow<FPlayerTableRow>(FName(*(FString::FormatAsNumber(Level))), FString(""));

	MaxHP = PlayerTableRow->MaxHp;
	CurrentHP = MaxHP;
	NextExp = PlayerTableRow->NextExp;
	CurrentATK = PlayerTableRow->Atk;
	ItemSlot = PlayerTableRow->Slot;
}
