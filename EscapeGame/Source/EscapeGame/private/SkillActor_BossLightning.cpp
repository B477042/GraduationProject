// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillActor_BossLightning.h"
#include "Sound/SoundCue.h"


ASkillActor_BossLightning::ASkillActor_BossLightning()
{
	loadAsset();
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Cap"));
	Capsule->SetupAttachment(RootComponent);
	Capsule->SetCollisionProfileName(TEXT("NoCollision"));
	bIsActivated = false;

	float X, Y, Z, Yaw, Roll, Pitch;
	VFX_Main->SetRelativeScale3D(FVector(X = 2.250000, Y = 1.000000, Z = 1.000000));

	SFX_Hit->SetRelativeLocation(FVector(X = 545.000000, Y = 0.000000, Z = 0.000000));

	Capsule->SetCapsuleHalfHeight(563.568665f);
	Capsule->SetCapsuleRadius(22.0f);
	Capsule->SetRelativeLocation(FVector(X = 545.000000, Y = 0.000000, Z = 0.000000));
	Capsule->SetRelativeRotation(FRotator(Pitch = -90.000000, Yaw = 0.000000, Roll = 0.000061));
	Timer = 0.0f;
	Limit = 3.0f;
	Damage = 17.0f;

	SetActorScale3D(FVector(1.295000, 2.265000, 1.275000));
}

void ASkillActor_BossLightning::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ASkillActor_BossLightning::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ASkillActor_BossLightning::OnCharacterOverlap);
}

void ASkillActor_BossLightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsActivated)return;
	//Rand하게 더해서 종료 시간을 다르게 한다
	Timer += DeltaTime ;
	if (Timer >= Limit)
	{
		Timer = 0;
		DeactivateEffect();
	}


}

bool ASkillActor_BossLightning::UseSkill(const FVector & Loc, const FRotator & Rot)
{
	return false;
}




void ASkillActor_BossLightning::ActivateEffect()
{
	VFX_Main->SetHiddenInGame(false);
	SFX_Hit->Play();

	Capsule->SetCollisionProfileName(TEXT("EnemyWeapon"));

	bIsActivated = true;
}

void ASkillActor_BossLightning::DeactivateEffect()
{
	SFX_Hit->Stop();
	VFX_Main->SetHiddenInGame(true);

	bIsActivated = false;
}

void ASkillActor_BossLightning::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}
	FDamageEvent DamageEvent;
	OtherActor->TakeDamage(Damage, DamageEvent,World->GetFirstPlayerController() ,this );
}

void ASkillActor_BossLightning::loadAsset()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem >PS_EFFECT(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_Beam.P_Beam'"));
	if (PS_EFFECT.Succeeded())
	{
		VFX_Main->SetTemplate(PS_EFFECT.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue>SB_SPARK(TEXT("SoundCue'/Game/MagicModule/SFX/CUE/CUE_LightingSparks.CUE_LightingSparks'"));
	if (SB_SPARK.Succeeded())
	{
		SFX_Hit->SetSound(SB_SPARK.Object);
		SFX_Hit->bAutoActivate = false;

	}



}
