// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_Player.h"
#include "EGPlayerController.h"
#include "DT_DataStruct.h"

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
	//������ �Ұ����ϰ� ���ش�
	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;
	ResetCombo();

	SetWalking();
}

void UStatComponent_Player::AddCombo(int32 Amount)
{
	CurrentCombo += Amount;
}

void UStatComponent_Player::ResetCombo()
{
	CurrentCombo = 0;
}

void UStatComponent_Player::GetExp(const int32 & DropExp)
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
