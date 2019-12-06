// Fill out your copyright notice in the Description page of Project Settings.

#include "Claymore.h"
//#include "..\public\Claymore.h"


AClaymore::AClaymore()
{
	PrimaryActorTick.bCanEverTick = true;
	



	MinDamage = 20.0f;
	MaxDamage = 40.0f;
	Timer = 0.0f;
	bIsActive = false;
	target = nullptr;

	initComponents();
	loadAssets();
	setRelativeCoordinates();
	setupCollision();
	
}



// Called when the game starts or when spawned
void  AClaymore::BeginPlay()
{
	Super::BeginPlay();

	ExplosionDelegate.AddUObject(this, &AClaymore::explosion);

}

// Called every frame
void  AClaymore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsActive)
	{
		Timer -= DeltaTime;
		if (Timer <= 0.0f)
			ExplosionDelegate.Broadcast();
	}
}

void AClaymore::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AClaymore::OnCharacterOverlap);
	Effect->OnSystemFinished.AddDynamic(this,&AClaymore::ClearMe);
}





void AClaymore::initComponents()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//Make Components Tree
	/*RootComponent = BoxCollision;
	Effect->SetupAttachment(Body);
	Body->SetupAttachment(RootComponent);
*/
	RootComponent = Body;
	Effect->SetupAttachment(Body);
	BoxCollision->SetupAttachment(RootComponent);
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


	
	Effect->bAutoActivate = false;


}

void AClaymore::setRelativeCoordinates()
{
	if (!Body->GetStaticMesh())return;
	

	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;
	float X = 0.0f, Y = 0.0f, Z = 0.0f;
//	Body->SetRelativeLocation(FVector((X = 90.000000f, Y = 0.000000f, Z = -30.000000f)));
	//Body->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
	Effect->SetRelativeRotation(FRotator(Pitch = 40.0000f, Yaw = 0.000000f, Roll = 0.000000f));
	Body->SetMobility(EComponentMobility::Static);
}

void AClaymore::setupCollision()
{
	Body->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollision->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	BoxCollision->SetGenerateOverlapEvents(true);


	BoxCollision->SetRelativeLocation(FVector( 0.0f,   90.0f,  30.000000f));
	BoxCollision->SetBoxExtent(FVector(100.0f, 113.015816f, 30.0f));
	BoxCollision->SetMobility(EComponentMobility::Static);
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
	if (!bIsActive)	return 0.0f;
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



void AClaymore::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	EGLOG(Error, TEXT("Actor Ditected"));
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (player == nullptr)return;


	target = player;
	EGLOG(Error, TEXT("Target Name : %s"), *target->GetName());
	Timer = 0.4;
	bIsActive = true;
}

void AClaymore::ClearMe(UParticleSystemComponent *Particle)
{
	Destroy();
}

void AClaymore::explosion()
{
	Body->SetHiddenInGame(true, false);
	BoxCollision->SetCollisionProfileName(TEXT("NoCollision"));
	
	Effect->Activate(true);

	FHitResult hitResult;
	FCollisionQueryParams param(NAME_None, false, this);

	bool result = GetWorld()->SweepSingleByChannel(hitResult, GetActorLocation(), target->GetActorLocation(),
		FQuat::MakeFromEuler(getNormalVectorDistance()),
		//Explosion
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(10.0f)
	);
	EGLOG(Error, TEXT("Target Name : %s"), *target->GetName());
	EGLOG(Error, TEXT("Distance : %f"), getDistance());
	if (result)
	{
		if (hitResult.Actor.IsValid())
		{

			EGLOG(Error, TEXT("%s has attacked by Claymore"), *hitResult.GetActor()->GetName());
			if (target == hitResult.GetActor())
			{
				
				target.Get()->TakeDamage(getDamage(),ActorTakeDamageEvent,target->GetController(),this);
			}
			
			else
			{
				EGLOG(Error, TEXT("That's not Player"));
			}
		}
	}
	bIsActive = false;


}
