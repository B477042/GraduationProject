// Fill out your copyright notice in the Description page of Project Settings.

#include "FireBallActor.h"
#include"EGPlayerCharacter.h"

// Sets default values
AFireBallActor::AFireBallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 0.001f;
	
	flyingTime = 0.0f;
	Damage = 20.0f;
	bIsFlying = false;
	
	initComponents();
	loadAssetes();
	setupCollision();
	

}

// Called when the game starts or when spawned
void AFireBallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireBallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	flying(DeltaTime);

	//ExplosionMe();
}

void AFireBallActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SoundTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFireBallActor::OnCharacterEntered);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AFireBallActor::OnCharacterHit);

	SoundExplosion->OnAudioFinished.AddDynamic(this,& AFireBallActor::DestroyMe);
}




void AFireBallActor::initComponents()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	FireBall = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FIREBALL"));
	ExplosionEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EXPLOSION"));
	HitEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HIT"));
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("COLLISION"));
	SoundTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	SoundCast = CreateDefaultSubobject<UAudioComponent >(TEXT("SOUNDCAST"));
	SoundExplosion= CreateDefaultSubobject<UAudioComponent >(TEXT("SOUNDEXPLOSION"));

	RootComponent = Root;
	Collision->SetupAttachment(RootComponent);
	FireBall->SetupAttachment(RootComponent);
	HitEffect->SetupAttachment(RootComponent);
	HitEffect->SetupAttachment(RootComponent);
	SoundCast->SetupAttachment(RootComponent);
	SoundExplosion->SetupAttachment(RootComponent);
	SoundTrigger->SetupAttachment(RootComponent);


}

void AFireBallActor::loadAssetes()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_FIREBALL(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_Fireball.P_Fireball'"));
	if (PS_FIREBALL.Succeeded())
	{
		FireBall->SetTemplate(PS_FIREBALL.Object);
		FireBall->SetRelativeScale3D(FVector(3.5f, 3.5f, 3.5f));
		//FireBall->bHiddenInGame = true;
		//FireBall->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_EXPLOSION(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_Explosion.P_Explosion'"));
	if (PS_EXPLOSION.Succeeded())
	{
		ExplosionEffect->SetTemplate(PS_EXPLOSION.Object);
		ExplosionEffect->bAutoActivate = false;
		ExplosionEffect->SetRelativeScale3D(FVector(3.5f, 3.5f, 3.5f));
		//ExplosionEffect->bHiddenInGame = true;

	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_HIT(TEXT("ParticleSystem'/Game/MagicModule/VFX/P_FireballHit.P_FireballHit'"));
	if (PS_HIT.Succeeded())
	{
		HitEffect->SetTemplate(PS_HIT.Object);
		HitEffect->bAutoActivate = false;
		HitEffect->SetRelativeScale3D(FVector(3.5f, 3.5f, 3.5f));
		//HitEffect->bHiddenInGame = true;
	}
	

		

	static ConstructorHelpers::FObjectFinder<USoundBase>SB_CAST(TEXT("SoundWave'/Game/MyFolder/Sound/SE/WAV_FireballCast.WAV_FireballCast'"));
	if (SB_CAST.Succeeded())
	{
		SoundCast->SetSound(SB_CAST.Object);
		SoundCast->bAutoActivate = false;
		SoundCast->Deactivate();
	}
	static ConstructorHelpers::FObjectFinder<USoundBase>SB_EXPLOSION(TEXT("SoundWave'/Game/MyFolder/Sound/SE/WAV_GroundExplosion01.WAV_GroundExplosion01'"));
	if (SB_EXPLOSION.Succeeded())
	{
		SoundExplosion->SetSound(SB_EXPLOSION.Object);
		SoundExplosion->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<USoundAttenuation >SA_Attenuation(TEXT("SoundAttenuation'/Game/MyFolder/Sound/FireBallCastAttenuation.FireBallCastAttenuation'"));
	if (SA_Attenuation.Succeeded())
	{
		SoundCast->AttenuationSettings = SA_Attenuation.Object;
		SoundExplosion->AttenuationSettings = SA_Attenuation.Object;
	}


}


void AFireBallActor::setupCollision()
{
	Collision->SetSphereRadius(40.3f);
	Collision->SetCollisionProfileName(TEXT("NoCollision"));
	SoundTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	SoundTrigger->SetSphereRadius(200.0f);
}


//맞으면 데미지 주고 터트리고
void AFireBallActor::OnCharacterHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult)
{
	//EGLOG(Error, TEXT("Hit"));

		FDamageEvent damageEvent;
		auto isPawn = Cast<APawn>(OtherActor);
		if (GetWorld()->GetFirstPlayerController()&&isPawn!=nullptr)
		{

			OtherActor->TakeDamage(Damage, damageEvent, GetWorld()->GetFirstPlayerController(), this);
		}
	
		//Collision->SetCollisionProfileName(TEXT("NoCollision"));
		ExplosionMe();


}

//날아가는 소리가 들리는 범위에 들어갔다면
void AFireBallActor::OnCharacterEntered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SoundCast->Play();
}

void AFireBallActor::ExplosionMe()
{
	//EGLOG(Error, TEXT("Explosion"));
	FireBall->Deactivate();
	FireBall->bHiddenInGame = true;
	Collision->Deactivate();

	bIsFlying = false;
	ExplosionEffect->Activate();
	HitEffect->Activate();

	SoundCast->Deactivate();
	SoundExplosion->Play();
	SoundTrigger->SetCollisionProfileName(TEXT("NoCollision"));
	Collision->SetCollisionProfileName(TEXT("NoCollision"));
}

void AFireBallActor::DestroyMe()
{
	//Destroy();

}

void AFireBallActor::flying(const float& DeltaTime)
{
	if (!bIsFlying)return;

	Speed += 0.6f;
	flyingTime += DeltaTime;
	if (DeltaTime >= MaxFlyingTime)
	{
		ExplosionMe();
		return;
	}

	FVector NewLocation = GetActorLocation() + (GetActorForwardVector()*Speed);
	SetActorLocation(NewLocation);
	//EGLOG(Error, TEXT("FireBall's pos: %s"), *GetActorLocation().ToString());
	
}

void AFireBallActor::Fire()
{
	//EGLOG(Error, TEXT("FireBall's forward vector : %s"),* GetActorForwardVector().ToString());

	bIsFlying = true;
	FireBall->bHiddenInGame=false;
	Collision->SetCollisionProfileName(TEXT("OverlapAll"));
	SoundTrigger->SetCollisionProfileName(TEXT("OnTrapTrigger"));

}
