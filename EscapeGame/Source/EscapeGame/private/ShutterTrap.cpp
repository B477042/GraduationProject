// Fill out your copyright notice in the Description page of Project Settings.

#include "ShutterTrap.h"
#include "EGPlayerCharacter.h"

// Sets default values
AShutterTrap::AShutterTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsActivated = false;
	Timer = 0.0f;
	initComponents();
	loadAssets();
	setupCollision();

}

// Called when the game starts or when spawned
void AShutterTrap::BeginPlay()
{
	Super::BeginPlay();

	////문제 코드
	for (int i = 0; i < n_spears; i++)
	{
		Spears.Emplace(GetWorld()->SpawnActor<ASpearActor>());
		if (Spears[i].IsValid())
		{

			Spears[i]->SetActorHiddenInGame(true);

			//?????? ??? ???
			//??? ?????? ??? ??? ??????? ????? ?????? ???´?
			//??? ???? ?? -> ?? ???????? ?????? ???. x,y????? ??? ???????
			FVector location = Root->GetComponentLocation() + FVector(100.0f - (50.0f*i), -10.0f, -120.0f);

			Spears[i]->SetActorRelativeLocation(location);
			Spears[i]->SetCollisionProfileTo(TEXT("NoCollision"));
		}

	}
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AShutterTrap::OnPlayerEntered);
	////setSpearsDefaultPos();
	
}


void AShutterTrap::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//setSpearsDefaultPos();
}

// Called every frame
void AShutterTrap::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if (!bIsActivated)return;

	Timer += DeltaTime;
	if (Timer <= StreachTime)
	{
		RiseUpSpears(DeltaTime);
	}
	else
	{
		
		PrimaryActorTick.bCanEverTick = false;
		bIsActivated = false;
		SoundEffect->Stop();
		EGLOG(Error, TEXT("Tick"));
	}
}



void AShutterTrap::RiseUpSpears(float deltaTime)
{
	//문제 있을 수 있는 코드
	float newZ=(spear_last-spear_start)/StreachTime*deltaTime;
	for (int i = 0; i < n_spears; i++)
	{
		 
		//EGLOG(Warning, TEXT("Rise!"));
		FVector newLocation = Spears[i]->GetActorLocation() + FVector(0.0f, 0.0f, newZ);
		Spears[i]->SetActorLocation(newLocation);
	}

}

void AShutterTrap::OnPlayerEntered(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (auto Player = Cast<AEGPlayerCharacter>(OtherActor) == nullptr)
		return;
	//Activate Tick 
	//PrimaryActorTick.bCanEverTick = true;
	for (int i=0;i<n_spears;i++)
	{
		Spears[i]->SetActorHiddenInGame(false);
		Spears[i]->SetCollisionProfileTo(TEXT("OnBlockingTypeTrap"));
	}
	SoundEffect->Play();
	bIsActivated = true;
	Trigger->SetCollisionProfileName(TEXT("NoCollision"));
}

void AShutterTrap::initComponents()
{
	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ROOT"));
	SoundEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("SE"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	RootComponent = Root;
	SoundEffect->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(RootComponent);
	
	float X, Y, Z;
	Trigger->SetRelativeLocation(FVector(X = 0.000000f, Y = -680.000000f, Z = 90.000000f));

	

}

void AShutterTrap::loadAssets()
{
	static ConstructorHelpers::FObjectFinder<USoundBase>SB_SOUND(TEXT("SoundWave'/Game/MyFolder/Sound/unsheath-sword.unsheath-sword'"));
	if (SB_SOUND.Succeeded())
	{
		SoundEffect->SetSound(SB_SOUND.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundAttenuation>SA_ATTENUATION(TEXT("SoundAttenuation'/Game/MyFolder/Sound/SparkAttenuation.SparkAttenuation'"));
	if(SA_ATTENUATION.Succeeded())
	{
		SoundEffect->AttenuationSettings = SA_ATTENUATION.Object;
	}

}

void AShutterTrap::setupCollision()
{
	Trigger->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	Trigger->SetBoxExtent(FVector(150.000000f, 70.000000f, 67.991219f));
	Trigger->SetGenerateOverlapEvents(true);
}

void AShutterTrap::setSpearsDefaultPos()
{
	//원점에서 창들이 솟은 지점을 바라볼 때, 그것이 일렬로 나열되어 있어야 한다. 그래야 길이 막히니까.
	//원점에서 box 콜리전까지 길이
	const float distToBox = Trigger->GetRelativeTransform().GetLocation().Y;
	const FVector CurrentPos = GetActorLocation();
	const FRotator CurrentRot = GetActorRotation();

	//Way 1

	////내가 사용하기 원하는 벡터는 전방벡터의 x,y값이 서로 스왑된 값이다. 그리고 내가 원하는 벡터의 x값은 -1이 곱해진다.
	////이렇게 한다면 벡터는 내쪽을 바라보게 된다
	//FVector newVec = GetActorForwardVector();
	//newVec.Y *= -1.0f;
	//const FVector myFwVec = FVector(newVec.Y, newVec.X, newVec.Z);

	////저 방향대로 디텍트 범위를 곱한후, 상대 좌표계에서 5개의 창의 중심점이 될 곳이 나올 것이다.
	//const FVector mySpearCenterPos = (myFwVec * distToBox) ;


	//원점으로 되돌린다.
	//그럼 상대좌표를 직접 지정해도 될 테니까
	SetActorRotation(FRotator::ZeroRotator);

	for (int i = 0; i < n_spears; i++)
	{
		Spears.Emplace(GetWorld()->SpawnActor<ASpearActor>());
		if (Spears[i].IsValid())
		{

			Spears[i]->SetActorHiddenInGame(true);

			////문제가 있는 코드
			////이거 때문에 창이 어느 방향이건 똑같은 방향에서 나온다
			////다시 만들 것 -> 값 조절에서 문제가 있다. x,y좌표를 다시 계산하자
			 
			FVector NewLocation = FVector(100.0f - (50.0f*i), -10.0f, -120.0f);
			//회전 반경
			FVector Radius = FVector(NewLocation.X, 0.0f, 0.0f);
			float Angle = CurrentRot.Yaw;
			FVector RotateValue = Radius.RotateAngleAxis(Angle, FVector(0.0f, 0.0f, 1.0f));
			NewLocation += RotateValue + CurrentPos;
			Spears[i]->SetActorRelativeLocation(NewLocation);
			
			//if(i%2==0)
			//Spears[i]->SetActorRelativeLocation(mySpearCenterPos + FVector(100.0f - (50.0f*i), -10.0f, -120.0f));
			
			

			Spears[i]->SetCollisionProfileTo(TEXT("NoCollision"));

			EGLOG(Warning, TEXT("Spear[%i]'s pos : %s"), i, *Spears[i]->GetTransform().GetLocation().ToString());
		}

	}

	//배치가 끝났으니 되돌린다
	SetActorRotation(CurrentRot);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AShutterTrap::OnPlayerEntered);

	EGLOG(Warning, TEXT("========================"));
	for (int i = 0; i < n_spears; i++)
	EGLOG(Warning, TEXT("Spear[%i]'s pos : %s"), i, *Spears[i]->GetTransform().GetLocation().ToString());

	//EGLOG(Error, TEXT("Claymore :%s ForwardVector : %s"), *GetName(), *GetActorForwardVector().ToString());
	//EGLOG(Warning, TEXT("Claymore :%s MyFwVec : %s"), *GetName(), *myFwVec.ToString());
	//EGLOG(Warning, TEXT("Claymore :%s myTargetVec : %s"), *GetName(), *myTargetVec.ToString());
}



