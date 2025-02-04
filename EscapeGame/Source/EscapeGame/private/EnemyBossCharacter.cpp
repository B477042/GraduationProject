// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBossCharacter.h"
#include "EnemyAIController_Boss.h"
#include "Boss_Fireball.h"
#include "EGSaveGame.h"
#include "EGGameInstance.h"
#include "AnimInstance_Boss.h"
#include "SkillActor_BossLightning.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sound/SoundCue.h"

AEnemyBossCharacter::AEnemyBossCharacter()
{
	AIControllerClass = AEnemyAIController_Boss::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	initComponents();
	loadAsset();

	bIsDamaged = false;
	State = EBossState::Walk;
	bIsMpCharging = false;
}

void AEnemyBossCharacter::BeginPlay()
{
	Super::BeginPlay();

	reloadSkillObjs();
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}

	/*UProgressBar**/

	HPBar = Cast<UProgressBar>(HPBarWidget->GetUserWidgetObject()->GetWidgetFromName(TEXT("HPBar")));
	if (!HPBar)
	{
		EGLOG(Warning, TEXT(" HPBar Failed"));
		return;
	}
	Stat->HPChangedDelegate.AddLambda([this]()->void {
		HPBar->SetPercent(Stat->GetHPRatio());
	});
	HPBar->SetPercent(Stat->GetHPRatio());

	SA_Thunder = World->SpawnActor<ASkillActor_BossLightning>();
	SA_Thunder->DeactivateEffect();

	/*Save & Load*/

	auto GameInstance = Cast<UEGGameInstance>(World->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Gameinstance is nullptr"));
		return;
	}
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AEnemyBossCharacter::LoadGame);
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AEnemyBossCharacter::SaveGame);



}

void AEnemyBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	GetCharacterMovement()->JumpZVelocity = 1000.0f;
	//죽을 준비를 시킨다
	Stat->HPZeroDelegate.AddLambda([this]()->void {
		auto OwnerCon = Cast<AEnemyAIController>(GetController());
		if (!OwnerCon)
		{
			EGLOG(Warning, TEXT("DEAD"));
			return;
		}OwnerCon->StopAI();
		auto Anim = GetMesh()->GetAnimInstance();
		Anim->StopAllMontages(0.0f);
		

	});




	//Comp_Fireball->AddSkillObj(ABoss_Fireball::CreateDefaultSubobject,10);
}

float AEnemyBossCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Stat->TakeDamage(FinalDamage);

//	EGLOG(Warning, TEXT("HP : %f"),Stat->GetHP());
	return FinalDamage;
}

void AEnemyBossCharacter::Attack()
{
}

bool AEnemyBossCharacter::TeleportTo(const FVector & DestLocation, const FRotator & DestRotation, bool bIsATest, bool bNoCheck)
{
	TeleportEnter->SetWorldLocation(GetActorLocation());
	TeleportEnter->Activate();
	TeleportSound->Play();
	bool bResult = Super::TeleportTo(DestLocation, DestRotation, bIsATest, bNoCheck);
	
	TeleportExit->SetWorldLocationAndRotation(DestLocation,GetActorRotation());
	TeleportExit->Activate();

	OnTeleportCalled.Broadcast();
	return bResult;

}


/*
불을 던지는 엑션

1) 정면으로 던진다
2) 
*/
void AEnemyBossCharacter::ThrowFireBall()
{
	auto tempCon = Cast<AEnemyAIController_Boss>(GetController());
	if (!tempCon) { 
		EGLOG(Warning, TEXT("Casting faile"));
		return; }

	AActor* tempObj = Cast<AActor>(tempCon->GetBlackboardComponent()->GetValueAsObject(AEnemyAIController_Boss::TargetPlayer));
	if (!tempObj)
	{
		EGLOG(Error, TEXT("fail to get value "));
		return;
	}
	//EGLOG(Warning, TEXT("Target Name : %s"), *tempObj->GetName());
	//tempCon->GetBlackBoard()->get (AEnemyAIController_Boss::TargetPlayer);
	Comp_Fireball->UseSkill(*tempObj,GetActorForwardVector());
	//EGLOG(Error, TEXT("FIRRRRR"));
	OnFireballThrow.Broadcast();

	
}

void AEnemyBossCharacter::Thunderbolt()
{
	OnThunderbolt.Broadcast();


}

void AEnemyBossCharacter::AtPlayThunderblotAnim()
{
	auto aiCon = Cast<AEnemyAIController_Boss>(GetController());
	if (!aiCon)
	{
		EGLOG(Error, TEXT("AI Con casting failed"));
		return;
	}

	FVector TargetPos = aiCon->GetBlackboardComponent()->GetValueAsVector(TEXT("TargetPos"));

	if (SA_Thunder->IsActivate()) { SA_Thunder->DeactivateEffect(); }


	//50%확률로 번개의 진행방향을 수직으로 할지 수평으로할지 정합니다.
	int rand = UKismetMathLibrary::RandomIntegerInRange(0, 10);

	if (rand < 5)
	{
		TargetPos -= FVector(0.0f, 0.0f, 200.0f);
		SA_Thunder->SetActorLocation(TargetPos);
		EGLOG(Warning, TEXT("Target Pois : %s"), *TargetPos.ToString())
			SA_Thunder->SetActorRotation(FRotator(90.0f, 0.0f, 0.0f));
		SA_Thunder->ActivateEffect();
	}
	else
	{

		FVector loc = GetActorLocation() + FVector(0.0f, 0.0f, 40.0f);
		SA_Thunder->SetActorLocation(loc);
		SA_Thunder->SetActorRotation(GetActorRotation());
		SA_Thunder->ActivateEffect();
	}

}

//Called By Task Node
void AEnemyBossCharacter::ChargeMP()
{
	//auto tempCon = Cast<AEnemyAIController_Boss>(GetController());
	//if (!tempCon) {
	//	EGLOG(Warning, TEXT("Casting faile"));
	//	return;
	//}

	
	//
	//EGLOG(Error, TEXT("Hi"));
	//	auto anim = Cast<UAnimInstance_Boss>(GetMesh()->GetAnimInstance());
	//	if (!anim)return;
	//	
	//	//anim->StopAllMontages(0.0f);

	//	anim->PlayChargeAnim();

	if (bIsMpCharging)return;
		OnChargeCalled.Broadcast();

		//bIsMpCharging = true;
		
	EGLOG(Error, TEXT("Hpi"));
	
	//tempCon->GetBlackBoard()->Get



}


void AEnemyBossCharacter::PlayChargeEffect(bool Power)
{
	//이펙트 켜기
	if (Power)
	{
		MpChargingEffect->Activate();
		MpChargingSound->Play();
	}
	//이펙트 끄기
	MpChargingEffect->Deactivate();
	MpChargingSound->Stop();


}

void AEnemyBossCharacter::initComponents()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	Comp_Fireball = CreateDefaultSubobject<USkillContainer_ProjectileType>(TEXT("FireballComp"));
	Stat = CreateDefaultSubobject<UStatComponent_Enemy>(TEXT("STAT"));
	TeleportEnter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TELEENTER"));
	TeleportExit = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TELEEXIT"));
	TeleportSound = CreateDefaultSubobject<UAudioComponent>(TEXT("TeleAUDIO"));
	TeleportSound->SetupAttachment(TeleportEnter);
	MpChargingEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MPCHARGING"));
	MpChargingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("MPCHARGINUDIO"));



	Stat->SetHP(3000.0f);
	Stat->SetMaxHP(3000.0f);
}

void AEnemyBossCharacter::loadAsset()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_BODY(TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));
	if (SM_BODY.Succeeded())
	{

		GetMesh()->SetSkeletalMesh(SM_BODY.Object);
		GetMesh()->SetRelativeLocation(FVector(0.000000f, 0.000000f, -90.000000f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("EenemyCharacter"));
	}
	
	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM_BOSS(TEXT("AnimBlueprint'/Game/MyFolder/AnimationBlueprint/Anim_Boss.Anim_Boss_C'"));
	if (ANIM_BOSS.Succeeded())
	{
		GetMesh()->SetAnimClass(ANIM_BOSS.Class);
		EGLOG(Warning, TEXT("jooooooo"));
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_TELEENTER(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Portal/FX/P_Portal_Teleport_Enter.P_Portal_Teleport_Enter'"));
	if (PS_TELEENTER.Succeeded())
	{
		TeleportEnter->SetTemplate(PS_TELEENTER.Object);
		TeleportEnter->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_TELEEXIT(TEXT("ParticleSystem'/Game/ParagonGideon/FX/Particles/Gideon/Abilities/Portal/FX/P_Portal_Teleport_Exit.P_Portal_Teleport_Exit'"));
	if (PS_TELEENTER.Succeeded())
	{
		TeleportExit->SetTemplate(PS_TELEEXIT.Object);
		TeleportExit->bAutoActivate = false;
	}
	//SoundCue'/Game/MagicModule/SFX/CUE/CUE_Teleport.CUE_Teleport'
	static ConstructorHelpers::FObjectFinder<USoundCue>SC_TELE(TEXT("SoundCue'/Game/MyFolder/Sound/SE/CUE_Teleport.CUE_Teleport'"));
	if (SC_TELE.Succeeded())
	{
		TeleportSound->SetSound(SC_TELE.Object);
		
		TeleportSound->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>CHARGING_EFFECT(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_InstantHeal.P_InstantHeal'"));
	if (CHARGING_EFFECT.Succeeded())
	{
		MpChargingEffect->SetTemplate(CHARGING_EFFECT.Object);
		MpChargingEffect->bAutoActivate = false;
		MpChargingEffect->SetupAttachment(RootComponent);
		MpChargingEffect->bAllowRecycling = true;

	}
	static ConstructorHelpers::FObjectFinder<USoundCue>SC_MP(TEXT("SoundCue'/Game/MyFolder/Sound/SE/CUE_Healing.CUE_Healing'"));
	if (SC_MP.Succeeded())
	{
		MpChargingSound->SetSound(SC_MP.Object);
		MpChargingSound->bAutoActivate = false;
		MpChargingSound->SetupAttachment(MpChargingEffect);
	
	}



}



void AEnemyBossCharacter::reloadSkillObjs()
{
	if (!GetWorld()) {
		EGLOG(Error, TEXT("Not World"));
		return;
	}

	int fbCapacity = Comp_Fireball->GetCapacity();
	EGLOG(Error, TEXT("Fb Cap[aitcy : %d"), fbCapacity);

	for (int i = 0; i < fbCapacity; i++)
	{
		Comp_Fireball->AddSkillObj(GetWorld()->SpawnActor<ABoss_Fireball>());
	}

}

void AEnemyBossCharacter::SaveGame(UEGSaveGame * SaveInstance)
{
	 
	//Super::SaveGame(SaveInstance);
	if (!SaveInstance)
	{
		EGLOG(Error, TEXT("SaveInstance is nullptr"));
		return;
	}
	
	FBossData SaveData;
	SaveData.Location = GetActorLocation();
	SaveData.Rotation = GetActorRotation();
	SaveData.bIsMpCharging = bIsMpCharging;
	
	auto DowncastedData = static_cast<FEnemyData*>(&SaveData);
	Stat->SaveGame(DowncastedData);


	
	auto AICon = Cast<AEnemyAIController_Boss>(GetController());
	if (!AICon)
		return;
	AICon->SaveGame(SaveData);

	SaveInstance->BossData = SaveData;
	EGLOG(Error, TEXT("Boss Save Complete mP : %f"), SaveInstance->BossData.MP);

}

void AEnemyBossCharacter::LoadGame(const UEGSaveGame * LoadInstance)
{
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("LoadInstance is nullptr"));
		return;
	}

	auto LoadData = LoadInstance->BossData;
	

	SetActorLocationAndRotation(LoadData.Location, LoadData.Rotation);
	bIsMpCharging = LoadData.bIsMpCharging;
	//UStruct Down Casting
	auto DowncastedData = static_cast<FEnemyData*>(&LoadData);


	EGLOG(Error, TEXT("Load instance data MP : %f"), LoadInstance->BossData.MP);
	auto AICon = Cast<AEnemyAIController_Boss>(GetController());
	if (!AICon)
	{
		return;
	}
	AICon->LoadGame(LoadData);
	Stat->LoadGame(DowncastedData);
}

