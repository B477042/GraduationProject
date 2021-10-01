// Fill out your copyright notice in the Description page of Project Settings.


#include "GruntCharacter.h"
#include "EnemyAIController_Grunt.h"
#include "CharacterAnimInstance.h"
//#include "DrawDebugHelpers.h"
#include "EGPlayerCharacter.h"
#include "EGSaveGame.h"
#include "EGGameInstance.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"


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
	
	StatComponent = CreateDefaultSubobject<UStatComponent_EGrunt>(TEXT("STAT"));
	VFX_MuzzleEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX_MuzzleEffect"));
	VFX_HitEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("VFX_HitEffect"));
	SFX_Explosion = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_EXPLOSION"));
	SFX_Burst = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Burst"));
	SFX_Death = CreateDefaultSubobject<UAudioComponent>(TEXT("SFX_Death"));

	

	/*
	*	VFX Muzzle Effect Settings
	* 
	*/
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Fire(TEXT("ParticleSystem'/Game/ParagonHowitzer/FX/Particles/Abilities/Primary/FX/P_Grenade_Muzzle.P_Grenade_Muzzle'"));
	if (PS_Fire.Succeeded())
	{
		VFX_MuzzleEffect->SetTemplate(PS_Fire.Object);
		VFX_MuzzleEffect->bAutoActivate = false;

	}
	/*
	 *	VFX Hit Effect Settings
	 *
	 */
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_Hit(TEXT("ParticleSystem'/Game/GrenadePack/Particles/VFX_GrenadeEXP_air.VFX_GrenadeEXP_air'"));
	if (PS_Hit.Succeeded())
	{
		VFX_HitEffect->SetTemplate(PS_Hit.Object);
		VFX_HitEffect->bAutoActivate = false;
	}
	/*
	 *	SFX Explosion Settings
	 * 
	 */
	static ConstructorHelpers::FObjectFinder<USoundBase>SB_EXPLOSION(TEXT("SoundWave'/Game/MyFolder/Sound/SE/WAV_GroundExplosion01.WAV_GroundExplosion01'"));
	if (SB_EXPLOSION.Succeeded())
	{
		SFX_Explosion->SetSound(SB_EXPLOSION.Object);
		SFX_Explosion->bAutoActivate = false;
	}
	/*static ConstructorHelpers::FObjectFinder<USoundAttenuation >SA_Attenuation(TEXT("SoundAttenuation'/Game/MyFolder/Sound/FireBallCastAttenuation.FireBallCastAttenuation'"));
	if (SA_Attenuation.Succeeded())
	{
		SFX_Explosion->AttenuationSettings = SA_Attenuation.Object;
	}*/

	/*
	 * SFX Burst Settings
	 */
	static ConstructorHelpers::FObjectFinder<USoundBase>SB_Burst(TEXT("SoundWave'/Game/MyFolder/Sound/SE/tow-missile-launch-1-no-echo.tow-missile-launch-1-no-echo'"));
	if (SB_EXPLOSION.Succeeded())
	{
		SFX_Burst->SetSound(SB_Burst.Object);
		SFX_Burst->bAutoActivate = false;
		SFX_Burst->SetupAttachment(RootComponent);
	}
	/*
	* SFX Death Settings
	*/
	static ConstructorHelpers::FObjectFinder<USoundBase>SB_Death(TEXT("SoundWave'/Game/MyFolder/Sound/Voice/334660__vultraz168__robotic-scream.334660__vultraz168__robotic-scream'"));
	{
		SFX_Death->SetSound(SB_Death.Object);
		SFX_Death->bAutoActivate = false;
		SFX_Death->SetupAttachment(RootComponent);
	}

	/*
	 *	SFX Sound Attenuation
	 * 
	 */
	static ConstructorHelpers::FObjectFinder<USoundAttenuation >SA_Burst(TEXT("SoundAttenuation'/Game/MyFolder/Sound/Attenuation_TowMissile.Attenuation_TowMissile'"));
	if (SA_Burst.Succeeded())
	{
		SFX_Burst->AttenuationSettings = SA_Burst.Object;
		SFX_Explosion->AttenuationSettings = SA_Burst.Object;
		SFX_Death->AttenuationSettings = SA_Burst.Object;
	}
	


	
	//Set Melee Attack Range To 100cm
	MeleeAttackRange = 240.0f;
	MeleeAttackExtent = FVector(100.0f,50.0f,50.0f);
	AtkMeleeAtk = 15.0f;
	AtkFireAtk = 25.0f;
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
 
	//CSV File을 기반으로 한 스텟 부여 설정
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
	StatComponent->HPChangedDelegate.AddLambda([this]()->void {
		HPBar->SetPercent(StatComponent->GetHPRatio());
	});
	HPBar->SetPercent(StatComponent->GetHPRatio());

	//Bind Muzzle Fire 
	Anim->OnFireAttack.BindUObject(this, &AGruntCharacter::PlayMuzzleEffect);

	/*Save & Load*/

	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Gameinstance is nullptr"));
		return;
	}
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AGruntCharacter::LoadGame);
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this, &AGruntCharacter::SaveGame);

}

void AGruntCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
	//Set Limit of Speeds

	if(StatComponent !=nullptr)
	StatComponent->SetSpeedLimits(MaxWalkingSpeed, MinWalkingSpeed, MaxRunningSpeed);

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
	

	});

	//체력이 0이 됐을 때 호출될 람다 함수
	StatComponent->HPZeroDelegate.AddLambda([this]()->void {
		auto Anim = Cast<UAnim_Grunt>(GetMesh()->GetAnimInstance());
		if (!Anim)
		{
			
			return;
		}

		EGLOG(Error, TEXT("%s is Down"),*GetName());

		if (Anim->IsAnyMontagePlaying())
		{
			Anim->StopAllMontages(0.0f);
		}

		Anim->PlayDeadAnim();
		


	});


}

float AGruntCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	StatComponent->TakeDamage(FinalDamage);
	

	//죽었다면 causer가 player인지 검사하고 경험치를 준다
	if (StatComponent->GetHPRatio() <= 0.0f)
	{
		auto player = Cast<AEGPlayerCharacter>(DamageCauser);
		if (player)
		{
			if (StatComponent->GetIsDamageable())
			{
				player->GetStatComponent()->GainExp(StatComponent->GetDropExp());
			}
		}
		StatComponent->SetDamageable(false);
	}



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

	auto SaveData = SaveInstance->D_Enemies.Find(GetName());
	if (!SaveData)
	{
		EGLOG(Error, TEXT("Can't find %s's Data"), *GetName());
		return;
	}

	
	
	StatComponent->SaveGame(SaveData);
	 

	
}


//Stat 관련 정보를 Load하면 된다. 위치 정보 불러오기는 부모에서 처리했다
void AGruntCharacter::LoadGame(const UEGSaveGame * LoadInstance)
{
	Super::LoadGame(LoadInstance);

	if (!GetOwner())
	{
		UE_LOG(LogTemp,Error, TEXT("Dead actor"));
		return;
	}

	auto LoadData = LoadInstance->D_Enemies.Find(GetName());
	if (!LoadData)
	{
		EGLOG(Error, TEXT("Can't find %s's Data"),*GetName());
		//Destroy();
		return;
	}

	StatComponent->LoadGame(LoadData);
	EGLOG(Error, TEXT("Find %s's Data"), *GetName());


}

void AGruntCharacter::PlayMuzzleEffect()
{
	
	VFX_MuzzleEffect->SetWorldLocation(	GetMesh()->GetSocketLocation(SockFirePointR));
	//Play Particle
	if(VFX_MuzzleEffect->IsActive())
	{
		VFX_MuzzleEffect->Deactivate();
	}

	VFX_MuzzleEffect->Activate();

	//Play Lunch Sounds
	if(SFX_Burst->IsActive())
	{
		SFX_Burst->Deactivate();
	}

	SFX_Burst->Activate();
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
	float DistOffset = 30.0f;
	//유효 사정거리
	float Range = 3000.0f;
	//원 지름
	float Radius = 200.0f;
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

	//디버그용 라인
//	DrawDebugLine(World, PosPSPlay, EndPoint, FColor::Cyan, false, 10.0f);


	
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
		VFX_HitEffect->SetWorldLocation(PosHit);
		SFX_Explosion->SetWorldLocation(PosHit);
		if(VFX_HitEffect->IsActive())
		{
			VFX_HitEffect->Deactivate();
		}
		if(SFX_Explosion->IsActive())
		{
			SFX_Explosion->Deactivate();
		}
		
		VFX_HitEffect->Activate();
		SFX_Explosion->Activate();
	}
	
}

void AGruntCharacter::PlayDeathEffect()
{
	VFX_HitEffect->SetWorldLocation(GetActorLocation());
	VFX_HitEffect->Activate();
	SFX_Explosion->SetWorldLocation(GetActorLocation());
	SFX_Explosion->Activate();
	SFX_Death->Activate();
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

