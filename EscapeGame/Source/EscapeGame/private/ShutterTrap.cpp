

#include "Actor/Trap/ShutterTrap.h"

#include "Actor/Character/EGPlayerCharacter.h"
#include "Components/AudioComponent.h"
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

	////���� �ڵ�
	for (int i = 0; i < n_spears; i++)
	{
		Spears.Emplace(GetWorld()->SpawnActor<ASpearActor>());
		if (Spears[i].IsValid())
		{

			Spears[i]->SetActorHiddenInGame(true);

			//?????? ??? ???
			//??? ?????? ??? ??? ??????? ????? ?????? ???��?
			//??? ???? ?? -> ?? ???????? ?????? ???. x,y????? ??? ???????
			SoundEffect->SetRelativeLocation(SoundEffect->GetRelativeLocation() + FVector(-90 + (30 * i), -6.0f + (1.5*i), -120.0f));
			FVector finallocation = SoundEffect->GetComponentLocation() ;

			Spears[i]->SetActorRelativeLocation(finallocation);
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
	//���� ���� �� �ִ� �ڵ�
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
	Root->SetCollisionProfileName(TEXT("NoCollision"));
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
	Trigger->SetRelativeLocation(FVector(X = 27.000027, Y = -337.981323, Z = 74.000000));

	

}

void AShutterTrap::loadAssets()
{
	static ConstructorHelpers::FObjectFinder<USoundBase>SB_SOUND(TEXT("SoundWave'/Game/MyFolder/Sound/SE/unsheath-sword.unsheath-sword'"));
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
	//�������� â���� ���� ������ �ٶ� ��, �װ��� �Ϸķ� �����Ǿ� �־�� �Ѵ�. �׷��� ���� �����ϱ�.
	//�������� box �ݸ������� ����
	const float distToBox = Trigger->GetRelativeTransform().GetLocation().Y;
	const FVector CurrentPos = GetActorLocation();
	const FRotator CurrentRot = GetActorRotation();

	//Way 1

	////���� ����ϱ� ���ϴ� ���ʹ� ���溤���� x,y���� ���� ���ҵ� ���̴�. �׸��� ���� ���ϴ� ������ x���� -1�� ��������.
	////�̷��� �Ѵٸ� ���ʹ� ������ �ٶ󺸰� �ȴ�
	//FVector newVec = GetActorForwardVector();
	//newVec.Y *= -1.0f;
	//const FVector myFwVec = FVector(newVec.Y, newVec.X, newVec.Z);

	////�� ������ ����Ʈ ������ ������, ��� ��ǥ�迡�� 5���� â�� �߽����� �� ���� ���� ���̴�.
	//const FVector mySpearCenterPos = (myFwVec * distToBox) ;


	//�������� �ǵ�����.
	//�׷� �����ǥ�� ���� �����ص� �� �״ϱ�
	SetActorRotation(FRotator::ZeroRotator);

	for (int i = 0; i < n_spears; i++)
	{
		Spears.Emplace(GetWorld()->SpawnActor<ASpearActor>());
		if (Spears[i].IsValid())
		{

			Spears[i]->SetActorHiddenInGame(true);

			////������ �ִ� �ڵ�
			////�̰� ������ â�� ��� �����̰� �Ȱ��� ���⿡�� ���´�
			////�ٽ� ���� �� -> �� �������� ������ �ִ�. x,y��ǥ�� �ٽ� �������
			 
			FVector NewLocation = FVector(100.0f - (50.0f*i), -10.0f, -120.0f);
			//ȸ�� �ݰ�
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

	//��ġ�� �������� �ǵ�����
	SetActorRotation(CurrentRot);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AShutterTrap::OnPlayerEntered);

	EGLOG(Warning, TEXT("========================"));
	for (int i = 0; i < n_spears; i++)
	EGLOG(Warning, TEXT("Spear[%i]'s pos : %s"), i, *Spears[i]->GetTransform().GetLocation().ToString());

	//EGLOG(Error, TEXT("Claymore :%s ForwardVector : %s"), *GetName(), *GetActorForwardVector().ToString());
	//EGLOG(Warning, TEXT("Claymore :%s MyFwVec : %s"), *GetName(), *myFwVec.ToString());
	//EGLOG(Warning, TEXT("Claymore :%s myTargetVec : %s"), *GetName(), *myTargetVec.ToString());
}



