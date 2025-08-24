// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstance_Boss.h"

#include "EscapeGame.h"
#include "Actor/Character/EnemyBossCharacter.h"
#include "Actor/Controller/EnemyAIController.h"
#include "Components/CapsuleComponent.h"

UAnimInstance_Boss::UAnimInstance_Boss()
{

	//static ConstructorHelpers::FObjectFinder <UAnimMontage>MON_CHARGE(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/Charge_Montage.Charge_Montage'"));
	//if (MON_CHARGE.Succeeded())
	//{
	//	HealMontage = MON_CHARGE.Object;
	//	EGLOG(Error, TEXT("ASDFFFFFFFFFFFFFFSADFSADFASDFASDGASDGAWSFBDFEBREWRGWEg"));
	//}

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
	EGLOG(Error, TEXT("*****"));
	auto Chara = Cast<AEnemyBossCharacter>(GetOwningActor());
	if (!Chara)return;
	
	EGLOG(Error, TEXT("**hhh***"));
	Chara->GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
//	StopAllMontages(0.0f);
	
	Chara->OnBossIsDead.Broadcast();
	
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

	//UGameplayStatics::OpenLevel(this,TEXT("Ending"));

}

void UAnimInstance_Boss::AnimNotify_ChargeStart()
{
	auto Chara = Cast<AEnemyBossCharacter>(GetOwningActor());
	if (!Chara)return;
	Chara->PlayChargeEffect(true);

}

void UAnimInstance_Boss::AnimNotify_ChargeEnd()
{
	auto Chara = Cast<AEnemyBossCharacter>(GetOwningActor());
	if (!Chara)return;
	Chara->SetCharging(false);

	auto AICon = Cast<AEnemyAIController>(Chara->GetController());
	if (!AICon)
		return;
	Chara->PlayChargeEffect(false);
	AICon->GetBlackboardComponent()->SetValueAsFloat(TEXT("MP"), 200.0f);
}

void UAnimInstance_Boss::PlayChargeAnim()
{
	//Montage_Play(HealMontage,1.0f);
}
