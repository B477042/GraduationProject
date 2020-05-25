// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Player.h"
#include "EGPlayerCharacter.h"
#include "Sound\SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "..\public\Anim_Player.h"


UAnim_Player::UAnim_Player()
{
	SoundLaugh = CreateDefaultSubobject<UAudioComponent>(TEXT("LAUGH"));
	SoundDeath = CreateDefaultSubobject<UAudioComponent>(TEXT("S_DEATH"));

	bIsGuarding = false;
	static ConstructorHelpers::FObjectFinder <UAnimMontage>NORMAL_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_NormalAttack.m_NormalAttack'"));
	if (NORMAL_ATTACK.Succeeded())
	{
		AttackMontage = NORMAL_ATTACK.Object;
	
	}
	//AnimMontage'/Game/MyFolder/AnimationBlueprint/Montage_Skill1.Montage_Skill1'

	static ConstructorHelpers::FObjectFinder <UAnimMontage>Skill_1(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/Montage_Skill1.Montage_Skill1'"));
	if (Skill_1.Succeeded())
	{
		SkillMontages.Add(Skill_1.Object);
	}


	static ConstructorHelpers::FObjectFinder <UAnimMontage>AIR_ATTACK(TEXT("AnimMontage'/Game/MyFolder/AnimationBlueprint/m_AirAttackMontage.m_AirAttackMontage'"));
	if (AIR_ATTACK.Succeeded())
	{
		AirAttackMontage = AIR_ATTACK.Object;
	}
	static ConstructorHelpers:: FObjectFinder<USoundCue>SC_Laugh(TEXT("SoundCue'/Game/ParagonKwang/Characters/Heroes/Kwang/Sounds/SoundCues/Kwang_Effort_Laugh.Kwang_Effort_Laugh'"));
	if (SC_Laugh.Succeeded())
	{
		SoundLaugh->SetSound(SC_Laugh.Object);
		SoundLaugh->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue>SC_Death(TEXT("SoundCue'/Game/ParagonKwang/Characters/Heroes/Kwang/Sounds/SoundCues/Kwang_Death.Kwang_Death'"));
	if (SC_Death.Succeeded())
	{
		SoundDeath->SetSound(SC_Death.Object);
		SoundDeath->bAutoActivate = false;
	}
	
	
	//UCharacterAnimInstance::StartCombo = 1;
	StartCombo = 1;
	EndCombo = 4;
	bIsDead = false;
	bIsRolling = false;
}

void UAnim_Player::JumpToComboAttackSection(int32 NewSection)
{
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
	
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
}

void UAnim_Player::JumpToChargetAttackSection(int32 NewSection)
{
	
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
}

//FName UAnim_Player::GetAttackMontageSectionName(int32 Section)
//{
//	
//
//	if (!FMath::IsWithinInclusive<int32>(Section, StartCombo, EndCombo))return FName(*FString::Printf(TEXT("Failed")));
//	return FName(*FString::Printf(TEXT("ComboAttack%d"), Section));
//
//}

//void UAnim_Player::PlayAttackMontage()
//{
//	//EGLOG(Warning, TEXT("Anim_Play montage"));
//	//Super::PlayAttackMontage();
//
//	;
//	/*if (!Montage_IsPlaying(NormalAttackMontage))
//	{*/
//
//
//	Montage_Play(AttackMontage, 1.0f);
//	/*	EGLOG(Warning, TEXT("Mon ATtack"));
//	}*/
//}

void UAnim_Player::PlayAirAttackMontage()
{
	Montage_Play(AirAttackMontage, 1.0f);

}

UAnimMontage * UAnim_Player::GetAttackMontage() const
{
	return AttackMontage;
}

void UAnim_Player::SetRolling(bool bResult)
{
	bIsRolling=bResult;
}
/*
	구르기 시작할 때 호출된다. 
	구르기 시작하면 데미지를 받지 않아야 된다.
	구르기 시작하면 그 방향으로만 굴러야 된다. 
*/
void UAnim_Player::AnimNotify_RollingStart()
{
	auto Owner = Cast<AEGPlayerCharacter>(GetOwningActor());
	if (Owner == nullptr)
	{
		EGLOG(Warning, TEXT("Animation Rolling's Owner actor is not Vailed"));
		return;
	}
	//
	Owner->GetMesh()->SetCollisionProfileName(TEXT("Rolling"));
//	Owner->bCanBeDamaged = false;
	EGLOG(Warning, TEXT("Actor Location : %s"), *Owner->GetActorLocation().ToString());
	EGLOG(Warning, TEXT("Mesh Location : %s"), *(Owner->GetActorLocation() +Owner->GetMesh()->GetRelativeLocation()).ToString());

}

void UAnim_Player::AnimNotify_RollingEnd()
{
	auto Owner = Cast<AEGPlayerCharacter>(GetOwningActor());
	if (Owner == nullptr)
	{
		EGLOG(Warning, TEXT("Animation Rolling's Owner actor is not Vailed in  RollingEnd"));
		return;
	}
	Owner->GetMesh()->SetCollisionProfileName(TEXT("PlayerCharacter"));
	//Owner->bCanBeDamaged = true;
	EGLOG(Warning, TEXT("Actor Location : %s"), *Owner->GetActorLocation().ToString());
	EGLOG(Warning, TEXT("Mesh Location : %s"), *(Owner->GetActorLocation() + Owner->GetMesh()->GetRelativeLocation()).ToString());
}

//Rolling Animation의 재생이 끝나면 호출 될 것이다. 
//Notify는 같은 스캘레톤 내부에서 이름을 공유하게 되니까 바꿔야겠다. 
void UAnim_Player::AnimNotify_AnimEnd()
{
	bIsRolling = false;

	auto Owner = Cast<AEGPlayerCharacter>(GetOwningActor());
	if (Owner == nullptr)
	{
		EGLOG(Warning, TEXT("Animation Rolling's Owner actor is not Vailed"));
		return;
	}
	EGLOG(Warning, TEXT("Actor Location : %s"), *Owner->GetActorLocation().ToString());
	EGLOG(Warning, TEXT("Mesh Location : %s"), *(Owner->GetActorLocation() + Owner->GetMesh()->GetRelativeLocation()).ToString());

	Owner->RecoverInput();
}

void UAnim_Player::AnimNotify_PlaySound()
{
	auto Owner = Cast<AEGPlayerCharacter>(GetOwningActor());
	if (Owner == nullptr)
	{
		
		return;
	}
	
	Owner->AttackSound->Play();


}

void UAnim_Player::AnimNotify_Skill1Start()
{
	EGLOG(Warning, TEXT("Jot na gin name "));
	SoundLaugh->Play();
}

void UAnim_Player::AnimNotify_SkillEnd()
{
	auto player = Cast<AEGPlayerCharacter>(GetOwningActor());

	if (!player)return;

	player->RecoverInput();
	StopAllMontages(0.0f);
	player->Stat->ResetCombo();
}

void UAnim_Player::AnimNotify_AnimNotify_ThunderStart()
{
	auto player = Cast<AEGPlayerCharacter>(GetOwningActor());

	if (!player)return;
	player->ActiveThunder();
}

void UAnim_Player::AnimNotify_DeadStart()
{
	auto player = Cast<AEGPlayerCharacter>(GetOwningActor());

	if (!player)return;
	SoundDeath->Play();
	player->RestricInput();
	player->GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	

}

void UAnim_Player::AnimNotify_DeadEnd()
{
	auto player = Cast<AEGPlayerCharacter>(GetOwningActor());

	if (!player)return;
	player->SetActorHiddenInGame(true);
	
	//FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	

}

//Input 값은 Player의 Combo
void UAnim_Player::PlaySkillMontage(int Combo)
{
	int playNum = Combo - 1;
	if (SkillMontages.IsValidIndex(playNum))
	{
		auto player = Cast<AEGPlayerCharacter>(GetOwningActor());

		if (!player)return;

		player->RestricInput();


		Montage_Play(SkillMontages[playNum],1.0f);

		

	}


}

void UAnim_Player::SetDead()
{
	bIsDead = true;
}
