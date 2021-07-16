// Fill out your copyright notice in the Description page of Project Settings.


#include "GruntCharacter.h"
#include "EnemyAIController_Grunt.h"
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

	/*
	 * Set AI Controller
	 */
	AIControllerClass = AEnemyAIController_Grunt::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	Stat = CreateDefaultSubobject<UStatComponent_EGrunt>(TEXT("STAT"));
	PSFireEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PSFireEffect"));
	/*
	* Load Fire Attack Particle
	*/
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Fire(TEXT("ParticleSystem'/Game/ParagonHowitzer/FX/Particles/Abilities/Primary/FX/P_Grenade_Muzzle.P_Grenade_Muzzle'"));
	if (PS_Fire.Succeeded())
	{
		PSFireEffect->SetTemplate(PS_Fire.Object);
		PSFireEffect->bAutoActivate = false;

	}

	//Set Melee Attack Range To 100cm
	MeleeAttackRange = 240.0f;
	MeleeAttackExtent = FVector(100.0f,50.0f,50.0f);
	AtkMeleeAtk = 10.0f;
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

	Anim = Cast<UAnim_Grunt>(GetMesh()->GetAnimInstance());
	if (!Anim)return;
	
	/*
	 *	Attack Event Delegate Add Lambda
	 *	람다 함수 바인딩
	 *	공격을 플레이할 때 호출되고 공격에 대한 판정을 시도합니다. 
	 * 
	 */
	Anim->AttackEvent_Delegate.AddLambda([this]()->void {
	FHitResult HitResult;
	FVector EndPoint = GetActorLocation() + GetActorForwardVector()*MeleeAttackRange;
	FCollisionQueryParams Params(NAME_None, false, this);

	//ECC_EngineTraceChannel2 = 'Player' Trace
	bool bResult = GetWorld()->SweepSingleByObjectType(HitResult, GetActorLocation(), EndPoint,
			FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeBox(MeleeAttackExtent),Params);

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
		Player->TakeDamage(AtkMeleeAtk, DamageEvent, GetController(), this);
		EGLOG(Warning, TEXT("Give Damgae : %d"), AtkMeleeAtk);
	}
	else
		EGLOG(Error, TEXT("Notjhiog"));

	});

	//체력이 0이 됐을 때 호출될 람다 함수
	Stat->HPZeroDelegate.AddLambda([this]()->void {
		auto anim = Cast<UAnim_Grunt>(GetMesh()->GetAnimInstance());
		if (!anim)
		{
			
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
		SetActorHiddenInGame(true);
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
	if (!Anim)return;
	
	
	Anim->PlayAttackMontage();



	
	

}

void AGruntCharacter::FireAttack()
{
	if (!Anim)return;
	//Montage 재생
	Anim->Montage_Play(Anim->GetFireAttackMontage());
	
	//발사 파티클을 만들 위치
	FVector PosPSPlay = GetMesh()->GetSocketLocation(SockFirePointR);
	//발사 파티클의 회전 값
	FRotator RotPSPlay = GetActorRotation();

	/*
	 *	발사 방식
	 *	Ray Tracing을 통한 타격 판정을 시행
	 *	원으로 스프레이 형식으로 만들어 랜덤한 방향으로 Ray를 발사
	 */

	// 발사 지점에서 원까지 거리 
	float DistOffset = 300.0f;
	//유효 사정거리
	float Range = 3000.0f;
	//원 지름
	float Radius = 50.0f;
	//원의 중심 위치
	FVector Center = PosPSPlay + (GetActorForwardVector() * DistOffset);
	//조준 지점. 원의 위치에서 랜덤하게 한다
	FVector AimPoint;
	AimPoint.X = FMath::RandRange(Center.X - Radius, Center.X + Radius);
	AimPoint.Y = FMath::RandRange(Center.Y - Radius, Center.Y + Radius);
	AimPoint.Z = FMath::RandRange(Center.Z - Radius, Center.Z + Radius);

	//Ray의 끝지점
	FVector EndPoint= AimPoint + (GetActorForwardVector() * Range);
	FHitResult HitResult;
	
	
	auto World = GetWorld();
	if(!World)
	{
		EGLOG(Warning, TEXT("World is invalid"));
		return;
	}
	//All Block Trace
	bool bResult = World->LineTraceSingleByChannel(HitResult, PosPSPlay, EndPoint, ECollisionChannel::ECC_GameTraceChannel4);
	//맞았다면
	if(bResult)
	{
		EGLOG(Warning, TEXT("Hit Target : %s"), *HitResult.Actor->GetName());
		//맞은 지점의 위치
		FVector PosHit= HitResult.ImpactPoint;
		//데미지 처리
		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(AtkFireAtk, DamageEvent, GetController(), this);
		//히트 판정 파티클&사운드 출력
		
	}
	
}


//삭제하기 전에 컨트롤러의 BT를 꺼준다
//콜리전은 꺼준다
//anim의 Dead Animation을 재생시키게 해준다
void AGruntCharacter::ReadToDead()
{
	auto con = Cast<AEnemyAIController_Grunt>(Controller);
	if (!con)return;


	con->StopAI();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	
	
	Anim->PlayDeadAnim();
}

