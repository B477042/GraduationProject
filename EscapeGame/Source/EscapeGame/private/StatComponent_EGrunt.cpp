// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_EGrunt.h"
#include "AICtrl_Grunt.h"
#include "DT_DataStruct.h"


UStatComponent_EGrunt::UStatComponent_EGrunt()
{

}


void UStatComponent_EGrunt::BeginPlay()
{
	Super::BeginPlay();
	loadDataTable();
}

void UStatComponent_EGrunt::loadDataTable()
{

	auto OwnerChara = Cast<ACharacter>(GetOwner());
	if (OwnerChara == nullptr)
	{
		EGLOG(Warning, TEXT("Owner is not Character class"));
		return;
	}
	auto OwnerCon = Cast<AAICtrl_Grunt>(OwnerChara->Controller);
	if (OwnerCon == nullptr)
	{
		EGLOG(Warning, TEXT("Owner controller Casting failed"));
		return;
	}

	auto DataTable = OwnerCon->GetDT_Grunt();

	//Set Enemy Stat Type by Random
	Type = FMath::FRandRange(1, 5);


	FEnemyTableRow* MyTable = DataTable->FindRow<FEnemyTableRow>(FName(*(FString::FormatAsNumber(Type))), FString(""));

	MaxHP = MyTable->MaxHp;
	CurrentHP = MaxHP;
	CurrentATK = MyTable->Atk;
	DropExp = MyTable->DropExp;

}

bool UStatComponent_EGrunt::IsDead()
{
	bool bResult = Super::IsDead();


	EGLOG(Warning, TEXT("Test Dead"));
	return bResult;
}