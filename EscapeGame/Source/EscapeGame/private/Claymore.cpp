// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trap/Claymore.h"

#include "Actor/Character/EGPlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
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
	//getPointForCheackBlock();
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

	
	FHitResult hitResult;

	bool bResult=bIsActorInFrontSide(hitResult);
	if (bResult)
	{
		changeBoxExtent(hitResult);
	}

	/*FVector blockingPos = FVector::ZeroVector;
	float distance = 0.0f;
	bool bResult=bCheackBlockingActor(blockingPos, distance);
	reSettingBoxSize(blockingPos, distance, bResult);
	EGLOG(Error, TEXT("claymore postinit"));*/
}





void AClaymore::initComponents()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO"));
	SwitchClickSound = CreateDefaultSubobject<UAudioComponent>(TEXT("CLICKSOUND"));
	//Make Components Tree
	/*RootComponent = BoxCollision;
	Effect->SetupAttachment(Body);
	Body->SetupAttachment(RootComponent);
*/
	RootComponent = Body;
	Effect->SetupAttachment(Body);
	BoxCollision->SetupAttachment(RootComponent);
	AudioEffect->SetupAttachment(Effect);
	SwitchClickSound->SetupAttachment(Effect);
}

void AClaymore::loadAssets()
{
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BODY(TEXT("/Game/MyFolder/Download_Object/m18a1.m18a1"));
	if (SM_BODY.Succeeded())
	{
		Body->SetStaticMesh ( SM_BODY.Object);
	}
	//set matrial color
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>Material_BODY(TEXT("MaterialInstanceConstant'/Game/MyFolder/My_Material/MaterialInstance/MI_Claymore.MI_Claymore'"));
	if (Material_BODY.Succeeded())
	{
		Body->SetMaterial(0,Material_BODY.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PS_EFFECT(TEXT("/Game/GrenadePack/Particles/VFX_GrenadeEXP_metal.VFX_GrenadeEXP_metal"));
	if (PS_EFFECT.Succeeded())
	{
		Effect->SetTemplate(PS_EFFECT.Object);
	}

	//SoundWave'/Game/GrenadePack/MapAssets/Audio/Explosion01.Explosion01'
	static ConstructorHelpers::FObjectFinder <USoundBase>AC_AUDIO(TEXT("SoundWave'/Game/MyFolder/Sound/SE/Explosion01.Explosion01'"));
	if (AC_AUDIO.Succeeded())
	{
		AudioEffect->SetSound(AC_AUDIO.Object);
	}
	static ConstructorHelpers::FObjectFinder <USoundBase>AC_CLICKAUDIO(TEXT("SoundWave'/Game/MyFolder/Sound/SE/car-seatbelt-clicking.car-seatbelt-clicking'"));
	if (AC_CLICKAUDIO.Succeeded())
	{
		SwitchClickSound ->SetSound(AC_CLICKAUDIO.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundAttenuation>SA_CLICK(TEXT("SoundAttenuation'/Game/MyFolder/Sound/ClickAttenuation.ClickAttenuation'"));
	if (SA_CLICK.Succeeded())
	{
		SwitchClickSound->AttenuationSettings = SA_CLICK.Object;
	}
	//SoundAttenuation'/Game/MyFolder/Sound/ClickAttenuation.ClickAttenuation'

	Effect->bAutoActivate = false;
	AudioEffect->bAutoActivate = false;
	SwitchClickSound->bAutoActivate = false;


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

	//�ִ� ������ ���� �ȿ� �ִٸ�
	if (distance < maxDamageRange)
		return MaxDamage;
	//���߿� ������ ������ �����
	if (distance < minDamageRange)
		return MinDamage;
	//������ ���
	else
		return 0.0f;
}

//max detect range�ȿ� ���Ͷ� �ε��ƴٸ� true
bool AClaymore::bIsActorInFrontSide(FHitResult &hitResult)
{

	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return false;
	}
		//FHitResult hitResult;
		FCollisionQueryParams param(NAME_None, false, this);
		
		const FVector ClaymorePos = Body->GetComponentLocation();

	//���� ����ϱ� ���ϴ� ���ʹ� ���溤���� x,y���� ���� ���ҵ� ���̴�. �׸��� ���� ���ϴ� ������ x���� -1�� ��������
		FVector newVec = GetActorForwardVector();
		newVec.Y *= -1.0f;
		const FVector myFwVec = FVector(newVec.Y, newVec.X, newVec.Z);

		//�� ������ ����Ʈ ������ ������, claymorePos�� ���ϸ� ���� ��ǥ�迡�� ����Ʈ ���� �� ���� ��ġ�� ���� ���� ���̴�.
		const FVector myTargetVec = (myFwVec * maxDetectRange) + ClaymorePos;

 

		//�������� detecte range��ŭ Ž���Ѵ�. ���̸� ���
		bool bResult = World->LineTraceSingleByChannel(hitResult, ClaymorePos , myTargetVec,
			//All Block Trace
			ECollisionChannel::ECC_GameTraceChannel4);
		//EdgePos = myTargetVec;
		
		if (!bResult)
		{
			//EGLOG(Error, TEXT("Nothing"));
			return false;
		}
	 
		return true;
}

//�ռ� ���� ����� �������� �ڽ��� �ٽ� �����Ѵ�. �ڽ��� ���̸� 
void AClaymore::changeBoxExtent(const FHitResult& hitResult)
{
	//Ž���� ���� ����
	const auto impactPoint = hitResult.ImpactPoint;

	float newBoxYPos=0.0f;
	float newBoxYLength=0.0f;
	

	//���� Box Extent�� ������ ���� �����Ѵ�. 100 100 30�� ���̴�
	//�ʱ�ȭ ���� ���� ���� ����� �Ѵ�
	FVector newBoxExtent = BoxCollision->GetScaledBoxExtent();
	FVector newBoxPos = BoxCollision->GetRelativeTransform().GetLocation();

	//���� ���ο� ��ġ�� ���̸� ����Ѵ�.
	newBoxYLength = FVector::Distance(hitResult.TraceStart,impactPoint)/2.0f;
	newBoxYPos = newBoxYLength;

	//��� �� ���� new vector�� �ִ´�
	newBoxExtent.Y = newBoxYLength;
	newBoxPos.Y = newBoxYPos;

	//���ο� ���� �����ؼ� �־��ش�
	BoxCollision->SetRelativeLocation(newBoxPos);
	BoxCollision->SetBoxExtent(newBoxExtent);
	
	//EGLOG(Warning, TEXT("Box Changed"));
	

}




void AClaymore::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//EGLOG(Error, TEXT("Actor Ditected"));
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (player == nullptr)return;

	
	target = player;
	//EGLOG(Error, TEXT("Target Name : %s"), *target->GetName());
	Timer = 0.4;
	bIsActive = true;
	SwitchClickSound->Play();
}

void AClaymore::ClearMe(UParticleSystemComponent *Particle)
{
	Destroy();
}

void AClaymore::explosion()
{
	auto World = GetWorld();
	if (!World)
	{
		EGLOG(Error, TEXT("World is null"));
		return;
	}

	Body->SetHiddenInGame(true, false);
	BoxCollision->SetCollisionProfileName(TEXT("NoCollision"));
	
	Effect->Activate(true);
	AudioEffect->Activate(true);
	FHitResult hitResult;
	FCollisionQueryParams param(NAME_None, false, this);

	FVector targetPos = target->GetActorLocation();

	bool result = World->SweepSingleByChannel(hitResult, GetActorLocation(), targetPos,
		FQuat::MakeFromEuler(getNormalVectorDistance(&targetPos)),
		//Explosion
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(0.1f)
	);
	EGLOG(Error, TEXT("Target Name : %s"), *target->GetName());
	EGLOG(Error, TEXT("Distance : %f"), getDistanceToTarget());
	if (result)
	{
		if (hitResult.GetActor())
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
