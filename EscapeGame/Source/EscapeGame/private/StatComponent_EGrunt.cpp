// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_EGrunt.h"
#include "AICtrl_Grunt.h"
#include "DT_DataStruct.h"
#include "GruntCharacter.h"
#include "EGSaveGame.h"


UStatComponent_EGrunt::UStatComponent_EGrunt()
{
	
}


void UStatComponent_EGrunt::BeginPlay()
{
	Super::BeginPlay();
	loadTypeData();
	//EGLOG(Error, TEXT("This Grunt's Type : %d"),Type);

}

void UStatComponent_EGrunt::loadTypeData()
{

	auto OwnerChara = Cast<AGruntCharacter>(GetOwner());
	if (OwnerChara == nullptr)
	{
		EGLOG(Warning, TEXT("Owner is not Character class"));
		return;
	}

	if (!OwnerChara->bAllowRandStat)return;

	auto OwnerCon = Cast<AAICtrl_Grunt>(OwnerChara->Controller);
	if (OwnerCon == nullptr)
	{
		EGLOG(Warning, TEXT("Owner controller Casting failed"));
		return;
	}

	auto DataTable = OwnerCon->GetDT_Grunt();

	////Set Enemy Stat Type by Random
	//Type = FMath::FRandRange(1, 5);

	if (Type != 0)
	{
		FEnemyTableRow* MyTable = DataTable->FindRow<FEnemyTableRow>(FName(*(FString::FormatAsNumber(Type))), FString(""));

		MaxHP = MyTable->MaxHp;
		CurrentHP = MaxHP;
		CurrentATK = MyTable->Atk;
		DropExp = MyTable->DropExp;

	}
	else
	{
		Type = FMath::FRandRange(1, 5);
		FEnemyTableRow* MyTable = DataTable->FindRow<FEnemyTableRow>(FName(*(FString::FormatAsNumber(Type))), FString(""));

		MaxHP = MyTable->MaxHp;
		CurrentHP = MaxHP;
		CurrentATK = MyTable->Atk;
		DropExp = MyTable->DropExp;
	}



}

bool UStatComponent_EGrunt::IsDead()
{
	bool bResult = Super::IsDead();

	/*
	EGLOG(Warning, TEXT("Test Dead"));
	if (bResult)
	{
		auto owner = Cast<AEnemyCharacter>(GetOwner());
		if (!owner)return bResult;

		

	}*/

	return bResult;
}

void UStatComponent_EGrunt::SaveGame(FEnemyData* SaveData)
{
	Super::SaveGame(SaveData);
	if (!SaveData)
	{
		EGLOG(Error, TEXT("Save Data is nullptr"));
		return;
	}

	
	SaveData->Type = Type;
	SaveData->Hp = CurrentHP;
	//return SaveData;
}

void UStatComponent_EGrunt::LoadGame(const FEnemyData* LoadData)
{
	Super::LoadGame(LoadData);
	if (!LoadData)
	{
		EGLOG(Error, TEXT("LoadData is nullptr"));
		return;
	}
	
	//EGLOG(Error, TEXT("LoadInstance Grunt's Type : %d"), LoadData->Type);

	Type = LoadData->Type;
	loadTypeData();
	SetHP(LoadData->Hp);

	//return LoadData;
}

