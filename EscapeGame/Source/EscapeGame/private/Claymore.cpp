// Fill out your copyright notice in the Description page of Project Settings.

#include "Claymore.h"
//#include "..\public\Claymore.h"


AClaymore::AClaymore()
{
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	MinDamage = 20.0f;
	MaxDamage = 40.0f;
	Timer = 0.0f;
	isActive = false;
	

	loadAssets();
	setRelativeCoordinates();
	setupCollision();

}



// Called when the game starts or when spawned
void  AClaymore::BeginPlay()
{
	Super::BeginPlay();

	SettingTrap();
	
	ExplosionDelegate.AddUObject(this, &AClaymore::explosion);

}

// Called every frame
void  AClaymore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isActive)
	{
		Timer -= DeltaTime;
		if (Timer <= 0.0f)
			ExplosionDelegate.Broadcast();
	}
}

void AClaymore::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AClaymore::ActivateTrap);
}

//플레이어가 탐지 범위에 들어온 시점
//타이머가 작동
//
void AClaymore::ActivateTrap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult)
{
	EGLOG(Error, TEXT("Actor Ditected"));
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (player == nullptr)return;

	//Body->bHiddenInGame = true;
	//Effect->Activate(true);
	//player->GetStatComponent()->TakeDamage(Damage);
	
	target = player;
	activeTimer();

}


void AClaymore::DeActivateTrap()
{
	
}

void AClaymore::ClearTrap()
{

}

void AClaymore::SettingTrap()
{
	//Effect->bHiddenInGame = true;

}

void AClaymore::loadAssets()
{
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BODY(TEXT("/Game/MyFolder/Download_Object/m18a1.m18a1"));
	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh ( SM_BODY.Object);
	}
	//set matrial color
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>Material_BODY(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Materials/Accessories/M_V_Grip_Green.M_V_Grip_Green"));
	if (Material_BODY.Succeeded())
	{
		Body->SetMaterial(0,Material_BODY.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_EFFECT(TEXT("/Game/GrenadePack/Particles/VFX_GrenadeEXP_metal.VFX_GrenadeEXP_metal"));
	if (PS_EFFECT.Succeeded())
	{
		Effect->SetTemplate(PS_EFFECT.Object);
	}


	//Make Components Tree
	RootComponent = Body;
	Effect->SetupAttachment(Body);
	BoxCollision->SetupAttachment(Body);

	Effect->bAutoActivate = false;


}

void AClaymore::setRelativeCoordinates()
{
	if (!Body->GetStaticMesh())return;
	

	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;

	Body->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
	Effect->SetRelativeRotation(FRotator(Pitch = 40.0000f, Yaw = 0.000000f, Roll = 0.000000f));
}

void AClaymore::setupCollision()
{
	
	BoxCollision->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	Body->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollision->SetGenerateOverlapEvents(true);


	BoxCollision->SetRelativeLocation(FVector(( 39.999947f,   109.999817f,  40.000000f)));
	BoxCollision->SetBoxExtent(FVector(99.491638f, 113.015816f, 35.989304f));

}

void AClaymore::activeTimer()
{
	isActive = true;
	Timer = 0.5;
}

void AClaymore::explosion()
{
	Body->bHiddenInGame = true;
	BoxCollision->SetCollisionProfileName(TEXT("OnExplosion"));
	
	Effect->Activate(true);

	FHitResult hitResult;
	FCollisionQueryParams param(NAME_None, false, this);
	
	bool result = GetWorld()->SweepSingleByChannel(hitResult, this->GetActorLocation(), target.Get()->GetActorLocation(),
		FQuat::MakeFromEuler(getNormalVectorDistance()),
		//Explosion
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(10.0f)
	);
	if (result)
	{
		if (hitResult.Actor.IsValid())
		{

			EGLOG(Error,TEXT("%s has attacked by Claymore"),*hitResult.GetActor()->GetName())
		}
	}
}

FVector AClaymore::getNormalVectorDistance()
{
	if (target != nullptr)
	{
		FVector temp=FVector::ZeroVector;
		auto pointB = target.Get()->GetActorLocation().GetSafeNormal();
		auto pointA = Body->GetComponentLocation().GetSafeNormal();
		
		temp = pointA - pointB;
		//EGLOG(Warning,TEXT("point A normalize : "))
		return temp;
			
	}
	else
		return FVector::ZeroVector;
	
}

float AClaymore::getDistance()
{
	if (target != nullptr)
		return FVector::Distance(Body->GetComponentLocation(), target.Get()->GetActorLocation());
	else
	return -1.0f;
}

float AClaymore::getDamage()
{
	if (!isActive)	return 0.0f;
	float distance = getDistance();
	if (distance == -1.0f)	return 0.0f;

	//최대 데미지 범위 안에 있다면
	if (distance < maxDamageRange)
		return MaxDamage;
	//나중에 데미지 프레임 만들기
	if (distance < minDamageRange)
		return MinDamage;
	//범위를 벗어남
	else
		return 0.0f;
}
