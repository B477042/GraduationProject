// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBossCharacter.h"
#include "AIController_Boss.h"
#include "Boss_Fireball.h"
#include "..\public\EnemyBossCharacter.h"

AEnemyBossCharacter::AEnemyBossCharacter()
{
	AIControllerClass = AAIController_Boss::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	initComponents();
	loadAsset();

	bIsDamaged = false;
	State = EBossState::Walk;
}

void AEnemyBossCharacter::BeginPlay()
{
	Super::BeginPlay();

	reloadSkillObjs();
	
}

void AEnemyBossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//Comp_Fireball->AddSkillObj(ABoss_Fireball::CreateDefaultSubobject,10);
}

float AEnemyBossCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return FinalDamage;
}

void AEnemyBossCharacter::Attack()
{
}


/*
불을 던지는 엑션

1) 정면으로 던진다
2) 
*/
void AEnemyBossCharacter::ThrowFireBall()
{
	auto tempCon = Cast<AAIController_Boss>(GetController());
	if (!tempCon) { 
		EGLOG(Warning, TEXT("Casting faile"));
		return; }

	AActor* tempObj = Cast<AActor>(tempCon->GetBlackboardComponent()->GetValueAsObject(AAIController_Boss::TargetPlayer));
	if (!tempObj)
	{
		EGLOG(Error, TEXT("fail to get value "));
		return;
	}
	EGLOG(Warning, TEXT("Target Name : %s"), *tempObj->GetName());
	//tempCon->GetBlackBoard()->get (AAIController_Boss::TargetPlayer);
	Comp_Fireball->UseSkill(*tempObj,GetActorForwardVector());
	//EGLOG(Error, TEXT("FIRRRRR"));
	OnFireballThrow.Broadcast();

	
}

void AEnemyBossCharacter::initComponents()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	Comp_Fireball = CreateDefaultSubobject<USkillComponent_ProjectileType>(TEXT("FireballComp"));
	Stat = CreateDefaultSubobject<UStatComponent_Enemy>(TEXT("STAT"));
	
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



}

void AEnemyBossCharacter::attachParticle()
{
	
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
