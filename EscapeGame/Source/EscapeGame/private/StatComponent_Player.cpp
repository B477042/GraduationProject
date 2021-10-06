// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent_Player.h"
#include "EGPlayerController.h"
#include "DT_DataStruct.h"
#include "EGGameInstance.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"


UStatComponent_Player::UStatComponent_Player()
{
	PrimaryComponentTick.bCanEverTick = true;
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

	static ConstructorHelpers::FObjectFinder<USoundWave>SW_LevelUp(TEXT("SoundWave'/Game/ParagonKwang/Characters/Heroes/Kwang/Sounds/SoundWaves/Kwang_DraftLock_020.Kwang_DraftLock_020'"));
	if (SW_LevelUp.Succeeded())
	{
		SFX_LevelUp = SW_LevelUp.Object;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_LevelUp(TEXT("ParticleSystem'/Game/ParagonKwang/FX/Particles/Abilities/Ultimate/FX/P_Kwang_Ult_Lightning.P_Kwang_Ult_Lightning'"));
	if (PS_LevelUp.Succeeded())
	{
		VFX_LevelUp = PS_LevelUp.Object;
		VFX_LevelUp->bAutoDeactivate = true;
	}
}

void UStatComponent_Player::InitializeComponent()
{
	Super::InitializeComponent();
}

void UStatComponent_Player::BeginDestroy()
{
	Super::BeginDestroy();

	//if (StaminaChangedDelegate.IsBound())
	//{
	//	StaminaChangedDelegate.Unbind();
	//}
	if (OnExpChanged.IsBound())
	{
		OnExpChanged.Unbind();
	}
	if (OnLevelUP.IsBound())
	{
		OnLevelUP.Unbind();
	}
}

void UStatComponent_Player::BeginPlay()
{
	Super::BeginPlay();
	LoadLevelData();


	if (OnLevelUP.IsBound())
	{
		OnLevelUP.Execute();
	}

}



void UStatComponent_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
	//bCanUsingStamina = true;
	//������ �Ұ����ϰ� ���ش�
	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;
	ResetCombo();

	SetWalking();
}

int32 UStatComponent_Player::GetLevel()
{
	return Level;
}

float UStatComponent_Player::GetExp()
{
	return Exp;
}

float UStatComponent_Player::GetExpRatio()
{
	float fExp = Exp;
	float fNextExp = NextExp;
	
	return (fExp <= 0.0f) ? 0.0f : fExp / fNextExp;
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
	UE_LOG(LogTemp, Log, TEXT("Player Gain Exp : %d "),DropExp); 
	/*EGLOG(Error, TEXT("Exp : %d"), Exp);
	EGLOG(Error, TEXT("Exp : %d"), NextExp);*/
	//if Level up
	if (Exp >= NextExp)
	{
		LevelUp();
		UE_LOG(LogTemp, Log, TEXT("Level Up"));
	}

	if (OnExpChanged.IsBound())
	{
		OnExpChanged.Execute();
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
//	auto OwnerActor = Cast<ACharacter>(GetOwner());
//	if (OwnerActor == nullptr)
//	{
//		EGLOG(Warning, TEXT("Owner is not Character class"));
//		return;
//	}
//	auto OwnerCon = Cast<AEGPlayerController>(OwnerActor->Controller);
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
	LoadLevelData();
	SetHP( newHp);
	Exp = newExp;

	if (OnLevelUP.IsBound())
	{
		OnLevelUP.Execute();
	}
	if (HPChangedDelegate.IsBound())
	{
		HPChangedDelegate.Broadcast();
	}

	
}

void UStatComponent_Player::LevelUp()
{
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}
	//Exp가 NextExp를 초과한 만큼 빼주고
	Exp -= NextExp;
	//0미만이면 Exp를 0으로 설정해준다
	if (Exp < 0)Exp = 0;
	++Level;
	
	LoadLevelData();
	if (OnLevelUP.IsBound())
	{
		OnLevelUP.Execute();
	}

	UGameplayStatics::PlaySound2D(this, SFX_LevelUp);
	UGameplayStatics::SpawnEmitterAtLocation(World, VFX_LevelUp, GetOwner()->GetTransform());

}

void UStatComponent_Player::LoadLevelData()
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

	if (!DataTable)
	{
		EGLOG(Error, TEXT("Table row null"));
		return;
	}
	PlayerTableRow = DataTable->FindRow<FPlayerTableRow>(FName(*(FString::FormatAsNumber(Level))), FString(""));

	MaxHP = PlayerTableRow->MaxHp;
	CurrentHP = MaxHP;
	NextExp = PlayerTableRow->NextExp;
	CurrentATK = PlayerTableRow->Atk;
	ItemSlot = PlayerTableRow->Slot;
}
