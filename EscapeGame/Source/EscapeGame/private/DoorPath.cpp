// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorPath.h"
#include "EGPlayerCharacter.h"
#include "Item_CardKey.h"

ADoorPath::ADoorPath()
{
	Door1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOOR1"));
	Door2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOOR2"));
	DoorGate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOORGATE"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_GATE(TEXT("/Game/StarterBundle/ModularScifiProps/Meshes/SM_GlassDoorway.SM_GlassDoorway"));
	if (SM_GATE.Succeeded())
	{
		DoorGate->SetStaticMesh(SM_GATE.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_DOOR(TEXT("/Game/MyFolder/SkeletalMeshs/SM_Gold_Door.SM_Gold_Door"));
	if (SM_DOOR.Succeeded())
	{
		Door1->SetStaticMesh(SM_DOOR.Object);
		Door2->SetStaticMesh(SM_DOOR.Object);

	}
	SetRelativePos();

	DoorGate->SetupAttachment(RootComponent);
	Door1->SetupAttachment(RootComponent);
	Door2->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(RootComponent);

	Trigger->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	Trigger->SetRelativeLocation(FVector(-160.0f, -320.0f, 110.0f));
	Trigger->SetBoxExtent(FVector(130.0f, 68.0f, 80.0f));
	bIsOpened = false;

}
//2019 10 07 나중에 시간에 따라 천천히 열리도록 조정
void ADoorPath::OpenTheDoor()
{
	bIsOpened = true;
	float X = 0.0f, Y = 0.0f, Z = 0.0f;
	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;
	Door1->SetRelativeLocation(FVector(X = -40.000000, Y = 20.000000, Z = 0.000000));
	Door1->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = -90.000000f, Roll = 0.000000f));

	Door2->SetRelativeLocation(FVector(X = -360.000000f, Y = 0.000000f, Z = 0.000000f));
	Door2->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = -90.000000f, Roll = 0.000000f));

	
}
//2019 10 07 나중에 시간에 따라 천천히 닫히도록 조정
void ADoorPath::CloseTheDoor()
{
	float X = 0.0f, Y = 0.0f, Z = 0.0f;
	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;
	Door1->SetRelativeLocation(FVector(X = -40.000000, Y = 20.000000, Z = 0.000000));
	Door1->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = -90.000000f, Roll = 0.000000f));

	Door2->SetRelativeLocation(FVector(X = -360.000000f, Y = 0.000000f, Z = 0.000000f));
	Door2->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = -90.000000f, Roll = 0.000000f));

}

void ADoorPath::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADoorPath::OnPlayerOverlap);
}

void ADoorPath::SetRelativePos()
{
	float X = 0.0f, Y = 0.0f, Z = 0.0f;
	float Pitch = 0.0f, Yaw = 0.0f, Roll = 0.0f;
	Door1->SetRelativeLocation(FVector(X = 20.000000f, Y = -10.000000f, Z = 0.000000f));
	
	
	Door2->SetRelativeLocation(FVector(X = -340.000000f, Y = 60.000000f, Z = 0.000000f));
	Door2->SetRelativeRotation(FRotator(Pitch = 0.000000f, Yaw = -180.000000f, Roll = 0.000000f));
	
	

	DoorGate->SetRelativeLocation(FVector(X = 20.000000f, Y = -10.000000f, Z = 0.000000f));
	
}

void ADoorPath::OnPlayerOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!player)return;
	//이미 열린 상태라면 반환
	if (bIsOpened)return;

	if (player->GetInventory()->UseItem(AItem_CardKey::Tag, player))
		OpenTheDoor();
	Trigger->SetCollisionProfileName(TEXT("NoCollision"));
	
}
