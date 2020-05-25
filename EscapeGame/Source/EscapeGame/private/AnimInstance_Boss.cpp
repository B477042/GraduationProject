// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Boss.h"
#include "EnemyBossCharacter.h"

#include "EnemyAIController.h"

UAnimInstance_Boss::UAnimInstance_Boss()
{

}

//void UAnimInstance_Boss::NativeBeginPlay()
//{
//	Super::NativeBeginPlay();
//
//
//
//
//}

void UAnimInstance_Boss::AnimNotify_DeadStart()
{
	auto Chara = Cast<AEnemyBossCharacter>(GetOwningActor());
	if (!Chara)return;
	auto OwnerCon = Cast<AEnemyAIController>(Chara->GetController());
	if (!OwnerCon)
	{
		EGLOG(Warning, TEXT("DEAD"));
		return;
	}

	Chara->GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));


	Chara->OnBossIsDead.Broadcast();
	OwnerCon->StopAI();
	StopAllMontages(0.0f);
	

}

void UAnimInstance_Boss::AnimNotify_DeadEnd()
{

	auto Chara = Cast<AEnemyBossCharacter>(GetOwningActor());
	if (!Chara)return;

	Chara->SetActorHiddenInGame(true);
	
	//Chara->GetCapsuleCompot()->SetCollisionProfileName(TEXT("NoCollision"));
	Chara->OnBossIsDead.Broadcast();
	
	Chara->Destroy();
}
