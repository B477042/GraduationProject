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
	getPointForCheackBlock();
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

	
	/*FVector blockingPos = FVector::ZeroVector;
	float distance = 0.0f;
	bool bResult=cheackBlockingActor(blockingPos, distance);
	reSettingBoxSize(blockingPos, distance, bResult);
	EGLOG(Error, TEXT("claymore postinit"));*/
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
	//Body->SetMobility(EComponentMobility::Static);
}

void AClaymore::setupCollision()
{
	Body->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollision->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	BoxCollision->SetGenerateOverlapEvents(true);


	BoxCollision->SetRelativeLocation(FVector( 0.0f,   100.0f,  30.000000f));
	BoxCollision->SetBoxExtent(FVector(100.0f, 100.0f, 30.0f));
	//BoxCollision->SetMobility(EComponentMobility::Static);
}




FVector AClaymore::getNormalVectorDistance(const FVector* Other)
{
	if (target != nullptr)
	{
		FVector temp=FVector::ZeroVector;
		auto pointB = Other->GetSafeNormal();
		auto pointA = Body->GetComponentLocation().GetSafeNormal();
		
		temp = pointA - pointB;
		//EGLOG(Warning,TEXT("point A normalize : "))
		return temp;
			
	}
	else
		return FVector::ZeroVector;
	
}

float AClaymore::getDistanceToTarget()
{
	if (target != nullptr)
		return FVector::Distance(Body->GetComponentLocation(), target.Get()->GetActorLocation());
	else
	return -1.0f;
}

float AClaymore::getDamage()
{
	if (!bIsActive)	return 0.0f;
	float distance = getDistanceToTarget();
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

bool AClaymore::cheackBlockingActor(FVector& BlockedLocation, float& DistanceToBlocked)
{
	

	FHitResult hitResult;
	FCollisionQueryParams param(NAME_None, false, this);
	

	auto tempPoint = getPointForCheackBlock();
	//전방으로 detecte range만큼 탐색한다. 
	bool bResult = GetWorld()->LineTraceSingleByChannel(hitResult, Body->GetComponentLocation() , tempPoint,
		//All Block Trace
		ECollisionChannel::ECC_GameTraceChannel4);
	

	// auto tempPoint = getPointForCheackBlock();
	////전방으로 detecte range만큼 탐색한다. 
	//bool bResult = GetWorld()->SweepSingleByChannel(hitResult, Body->GetComponentLocation(), tempPoint,
	//	FQuat::MakeFromEuler(getNormalVectorDistance(&tempPoint)),
	//	//All Block Trace
	//	ECollisionChannel::ECC_GameTraceChannel4,
	//	FCollisionShape::MakeSphere(0.01f));


	////탐색 결과 있다면 그것의 true
	if (bResult)
	{
		EGLOG(Error,TEXT("Actor Name : %s BodyComponent Location : %s"),*GetName(),*Body->GetComponentLocation().ToString())
		EGLOG(Error, TEXT("Detected Point Location : %s"), *hitResult.Location.ToString());
		EGLOG(Error, TEXT("Detected Point : impactPoint %s"), *hitResult.ImpactPoint.ToString());

		BlockedLocation =  hitResult.Location;
		DistanceToBlocked = FVector::Distance(GetActorLocation(), BlockedLocation);
		return true;
	}

	// 없다면, nullptr리턴
	else
	{
		EGLOG(Error, TEXT("No"));
		return false;
	}
		
	
}
//전방 벡터를 기준으로 탐지 거리까지의 거리를 구해준다. 
FVector AClaymore::getPointForCheackBlock()
{
	//FVector result =GetActorLocation();
	FVector result =Body->GetComponentLocation();
	
	FVector FW = GetActorForwardVector();

	FVector axisY(0.0f, 1.0f, 0.0f);
	result.Z = 0.0f; FW.Z = 0.0f;

	float dotProduct = FVector::DotProduct(FW, axisY);
	/*EGLOG(Warning, TEXT("%f"), FVector::DotProduct(FW, axisY));*/
	float arcCos = FMath::Acos(dotProduct);
	float angle = FMath::RadiansToDegrees(arcCos);
	//EGLOG(Warning, TEXT("arcCos : %f cos: %f"), arcCos,angle);
	//EGLOG(Warning, TEXT("cos 90 = %f"), FMath::Cos(60.0f));
	/*
		dot Product 를 하면 두 벡터가 이루는 각도의 cos 값이 리턴된다

	*/
	//float cosA = FMath::Acos(FVector::DotProduct(FW, axisY));
	//
	//float sinA= FMath::Asin(FVector::DotProduct(FW, axisY));
	
	FVector pointA(FMath::Cos(arcCos)*maxDetectRange, FMath::Sin(arcCos)*maxDetectRange, 0.0f);
	//EGLOG(Error, TEXT("Actor : %s's pointA %f %f %f"), *GetName(), pointA.X, pointA.Y, pointA.Z);
	result = pointA +result;
	result.Z = Body->GetComponentLocation().Z;
	EGLOG(Error, TEXT("result : %s distance point %f %f %f"), *GetName(), result.X, result.Y, result.Z);
	return result;
}

void AClaymore::reSettingBoxSize(FVector& BlockedLocation, float& DistanceToBlocked, bool bResult)
{
	if (!bResult)return;

	FVector newBoxCollisionPos = (Body->GetComponentLocation() +BlockedLocation)/2.0f;
	BoxCollision->SetBoxExtent(FVector(100.000000f, DistanceToBlocked/2.0f, 30.000000f));
	BoxCollision->SetRelativeLocation(newBoxCollisionPos);
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

	FVector targetPos = target->GetActorLocation();

	bool result = GetWorld()->SweepSingleByChannel(hitResult, GetActorLocation(), targetPos,
		FQuat::MakeFromEuler(getNormalVectorDistance(&targetPos)),
		//Explosion
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(0.1f)
	);
	EGLOG(Error, TEXT("Target Name : %s"), *target->GetName());
	EGLOG(Error, TEXT("Distance : %f"), getDistanceToTarget());
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
