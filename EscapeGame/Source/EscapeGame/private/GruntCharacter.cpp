// Fill out your copyright notice in the Description page of Project Settings.


#include "GruntCharacter.h"
#include "AICtrl_Grunt.h"
#include "CharacterAnimInstance.h"
//#include "DrawDebugHelpers.h"
#include "EGPlayerCharacter.h"
#include "EGSaveGame.h"
#include "EGGameInstance.h"

//const float AGruntCharacter::MaxHP = 200.0f;
const float AGruntCharacter::MinWalkingSpeed = 0.0f;
const float AGruntCharacter::MaxWalkingSpeed = 200.0f;
const float AGruntCharacter::MaxRunningSpeed = 700.0f;


AGruntCharacter::AGruntCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set AI Controller
	AIControllerClass = AAICtrl_Grunt::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	Stat = CreateDefaultSubobject<UStatComponent_EGrunt>(TEXT("STAT"));
	
	//Set Attack Range To 100cm
	AttackRange = 240.0f;
	AttackExtent = FVector(100.0f,50.0f,50.0f);
	ATK = 10.0f;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM_Body(TEXT("SkeletalMesh'/Game/ParagonHowitzer/Characters/Heroes/Howitzer/Skins/Tier_2/Domed/Meshes/Howitzer_Domed.Howitzer_Domed'"));
	if (SM_Body.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Body.Object);

		GetMesh()->SetRelativeLocation(FVector( 0.000000f, 0.000000f,-122.000000f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
	GetCapsuleComponent()->SetCapsuleHalfHeight(122.208832f);
	GetCapsuleComponent()->SetCapsuleRadius(63.929523f);


	static ConstructorHelpers::FClassFinder <UAnimInstance>CA_Anim(TEXT("/Game/MyFolder/AnimationBlueprint/GruntAnim.GruntAnim_C"));
	if (CA_Anim.Succeeded())
	{
		
		GetMesh()->SetAnimClass(CA_Anim.Class);
		//EGLOG(Warning, TEXT("Anim!!!!"));
	}
	else
		EGLOG(Warning, TEXT("Faile"));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//Stat = CreateDefaultSubobject<UStatComponent_Enemy>(TEXT("STAT"));
	//if (Stat == nullptr)EGLOG(Warning, TEXT("Enemy's Stat is null"));

	bAllowRandStat = true;
}

void AGruntCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Check Direction of This Actor. Will Draw a line that point to Front 2m
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector()*200.0f,FColor ::Red, true);
	
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
	
}

void AGruntCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
	//Set Limit of Speeds

	if(Stat!=nullptr)
	Stat->SetSpeedLimits(MaxWalkingSpeed, MinWalkingSpeed, MaxRunningSpeed);

	auto Anim = Cast<UAnim_Grunt>(GetMesh()->GetAnimInstance());
	if (!Anim)return;

	//공격을 플레이할 때 호출되고 공격에 대한 판정을 시도합니다. 이걸 넣어줍니다
	Anim->AttackEvent_Delegate.AddLambda([this]()->void {
		
	//EGLOG(Error, TEXT("ANIm notify test start"));
	FHitResult HitResult;
	FVector EndPoint = GetActorLocation() + GetActorForwardVector()*AttackRange;
	FCollisionQueryParams Params(NAME_None, false, this);

	//ECC_EngineTraceChannel2 = 'Player' Trace
	bool bResult = GetWorld()->SweepSingleByObjectType(HitResult, GetActorLocation(), EndPoint,
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(AttackExtent),Params);

	//if hit
	if (bResult)
	{
		auto Player = Cast<AEGPlayerCharacter>(HitResult.GetActor());
		if (Player == nullptr)
		{
			EGLOG(Warning, TEXT("Casting Error"));
			return;
		}

		FDamageEvent DamageEvent;
		Player->TakeDamage(ATK, DamageEvent, GetController(), this);
		EGLOG(Warning, TEXT("Give Damgae : %d"), ATK);
	}
	else
		EGLOG(Error, TEXT("Notjhiog"));

	});

	//체력이 0이 됐을 때 호출될 함수들을 엮어줍니다
	//Stat->HPZeroDelegate.AddUObject(this, &AGruntCharacter::ReadToDead);
	//Stat->HPZeroDelegate.AddUObject(this, UAnim_Grunt::playDeadAnim);
	Stat->HPZeroDelegate.AddLambda([this]()->void {
		auto anim = Cast<UAnim_Grunt>(GetMesh()->GetAnimInstance());
		if (!anim)
		{
			EGLOG(Warning, TEXT("Dead failed555555555555555555555555555555555555555555555555555555"));
			return;
		}

		EGLOG(Error, TEXT("%s is Down"),*GetName());

		anim->PlayDeadAnim();
	});


	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Gameinstance is nullptr"));
		return;
	}
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AGruntCharacter::LoadGame);
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AGruntCharacter::SaveGame);

}

float AGruntCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Stat->TakeDamage(FinalDamage);
	



	return FinalDamage;
}


//Stat과 관련된 정보를 저장하면 된다. 
void AGruntCharacter::SaveGame(UEGSaveGame * SaveInstance)
{
	Super::SaveGame(SaveInstance);
	if (!SaveInstance)
	{
		EGLOG(Error, TEXT("Save Instance is nullptr"));
		return;
	}

	auto SaveData = SaveInstance->D_Enemies.Find(GetOwner()->GetName());
	if (!SaveData)
	{
		EGLOG(Error, TEXT("Can't find %s's Data"), *GetOwner()->GetName());
		return;
	}

	
	
	Stat->SaveGame(SaveData);
	 

	
}


//Stat 관련 정보를 Load하면 된다. 위치 정보 불러오기는 부모에서 처리했다
void AGruntCharacter::LoadGame(const UEGSaveGame * LoadInstance)
{
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("LoadInstance is nullptr"));
		return;
	}

	auto LoadData = LoadInstance->D_Enemies.Find(GetOwner()->GetName());
	if (!LoadData)
	{
		EGLOG(Error, TEXT("LaodData FAILED"));
		return;
	}

	Stat->LoadGame(LoadData);



}



void AGruntCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	//FVector DPoint = GetActorLocation()+GetMesh()->GetForwardVector()*500.0f;
	//DrawDebugLine(GetWorld(), GetActorLocation(), DPoint, FColor::Cyan, false);
}

void AGruntCharacter::Attack()
{
	//EGLOG(Warning, TEXT("Attack! Grunt"));

	
	auto Anim = Cast<UAnim_Grunt>(GetMesh()->GetAnimInstance());
	if (!Anim)return;
	Anim->PlayAttackMontage();



	
	

}


//삭제하기 전에 컨트롤러의 BT를 꺼준다
//콜리전은 꺼준다
//anim의 Dead Animation을 재생시키게 해준다
void AGruntCharacter::ReadToDead()
{
	auto con = Cast<AAICtrl_Grunt>(Controller);
	if (!con)return;


	con->StopAI();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	
	auto Anim = Cast<UAnim_Grunt>(GetMesh()->GetAnimInstance());
	if (!Anim)return;
	Anim->PlayDeadAnim();
}

