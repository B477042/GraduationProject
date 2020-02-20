// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_Player.h"

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
}

void UStatComponent_Player::InitializeComponent()
{
	Super::InitializeComponent();
}

void UStatComponent_Player::BeginPlay()
{
	Super::BeginPlay();
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

	SetFreeMove();
}

void UStatComponent_Player::AddCombo(int32 Amount)
{
	CurrentCombo += Amount;
}

void UStatComponent_Player::ResetCombo()
{
	CurrentCombo = 0;
}

void UStatComponent_Player::LoadDataTable(const UDataTable * DataTable)
{
	/*
	*	First, Get Player controller Static class
	*	Second, Bring DataTable from PlayerController
	*	Third, Compare Inputted Data Table To Controller's Table
	*
	*/
	
	if (DataTable == nullptr) { EGLOG(Warningt, TEXT("inputted Data Table is nullptr")); return; }
	
	FPlayerTableRow* PlayerTableRow = DataTable->FindRow<FPlayerTableRow>(FName(*(FString::FormatAsNumber(Level))),FString(""));
	
	//LevelUpDataTable->FindRow<FLevelUpTableRow>(FName(*(FString::FormatAsNumber(i))), FString(""));

	if(PlayerTableRow==nullptr) { EGLOG(Warningt, TEXT("Player Table Row is nullptr")); return; }

	PlayerTableRow->ShowInfo();
	

}
