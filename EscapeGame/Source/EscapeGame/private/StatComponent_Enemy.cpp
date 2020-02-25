// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_Enemy.h"
#include "DT_DataStruct.h"
#include "EnemyAIController.h"

UStatComponent_Enemy::UStatComponent_Enemy()
{
	MinWalkingSpeed = 0.0f;
	MaxWalkingSpeed = 350.0f;
	MaxRunningSpeed = 700.0f;
}

void UStatComponent_Enemy::InitializeComponent()
{
	Super::InitializeComponent();
}

void UStatComponent_Enemy::BeginPlay()
{
	Super::BeginPlay();
	loadDataTable();
}

void UStatComponent_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UStatComponent_Enemy::GetDropExp()
{
	return DropExp;
}

void UStatComponent_Enemy::loadDataTable()
{

	auto OwnerChara = Cast<ACharacter>(GetOwner());
	if (OwnerChara == nullptr)
	{
		EGLOG(Warning, TEXT("Owner is not Character class"));
		return;
	}
	auto OwnerCon = Cast<AEnemyAIController>(OwnerChara->Controller);
	if (OwnerCon == nullptr)
	{
		EGLOG(Warning, TEXT("Owner controller Casting failed"));
		return;
	}

	auto DataTable = OwnerCon->GetDT_Grunt();

	//Set Enemy Stat Type by Random
	Type = FMath::FRandRange(1, 5);


	FEnemyTableRow* MyTable = DataTable->  FindRow<FEnemyTableRow>(FName(*(FString::FormatAsNumber(Type))), FString(""));

	MaxHP = MyTable->MaxHp;
	CurrentHP = MaxHP;
	CurrentATK = MyTable->Atk;
	DropExp = MyTable->DropExp;

}
