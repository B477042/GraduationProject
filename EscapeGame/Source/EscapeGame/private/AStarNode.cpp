// Fill out your copyright notice in the Description page of Project Settings.

#include "AStarNode.h"
#include "EGPlayerCharacter.h"

// Sets default values
AAStarNode::AAStarNode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	initComponents();
	bIsPath = false;
	bIsVisited = false;

	Count_F = 0;
	Count_G = 0;
	Count_H = 0;

}

// Called when the game starts or when spawned
void AAStarNode::BeginPlay()
{
	Super::BeginPlay();

	Deactivate();
}

void AAStarNode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAStarNode::OnActorOverlap);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AAStarNode::OnActorOverlapEnd);
}

void AAStarNode::OnActorOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!player)return;

	Deactivate();
	



}

void AAStarNode::OnActorOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (bIsPath)
			Activate();
}

// Called every frame
void AAStarNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AAStarNode::operator<(const AAStarNode & lhs)
{

	return Count_F<lhs.Count_F;
}

//bool AAStarNode::operator<(const AAStarNode & lhs, const AAStarNode & rhs)
//{
//	return lhs.Count_F<rhs.Count_F;
//}



bool AAStarNode::operator>(const AAStarNode & lhs)
{
	return Count_F > lhs.Count_F;
}

bool AAStarNode::operator==(const AAStarNode & lhs)
{
	return  Count_F == lhs.Count_F;
}

void AAStarNode::SortNearNodes()
{
	
	


}



void AAStarNode::Activate()
{
	BodyMesh->SetHiddenInGame(false);
}

void AAStarNode::Deactivate()
{
	BodyMesh->SetHiddenInGame(true);
}

void AAStarNode::SetRoad(bool bResult)
{
	bIsPath = bResult;
}






void AAStarNode::initComponents()
{
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMESH"));
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BOXTRigger"));

	RootComponent = BoxTrigger;
	BodyMesh->SetupAttachment(RootComponent);

	BoxTrigger->SetCollisionProfileName(TEXT("OnTrapTrigger"));
	BodyMesh->SetCollisionProfileName(TEXT("NoCollision"));
	float X, Y, Z;
	BoxTrigger->SetBoxExtent(FVector(X = 70.225533f, Y = 62.159767f, Z = 37.897743f));
	BodyMesh->SetRelativeRotation(FRotator(0.0f, 45.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder <UStaticMesh>SM_MESH(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (SM_MESH.Succeeded())
	{
		BodyMesh->SetStaticMesh(SM_MESH.Object);
		//MaterialInstanceConstant'/AnimationSharing/AnimSharingGreen.AnimSharingGreen'
	}
	static ConstructorHelpers::FObjectFinder <UMaterialInstance>MATERIAL_GREEN(TEXT("MaterialInstanceConstant'/AnimationSharing/AnimSharingGreen.AnimSharingGreen'"));
	if (MATERIAL_GREEN.Succeeded())
	{
		BodyMesh->SetMaterial(0, MATERIAL_GREEN.Object);

	}

	NearNodes.Init(nullptr, 4);

}

int AAStarNode::CalcGCount(const FVector & Start)
{
	Count_G = FVector::Distance(Start, GetActorLocation());
	return Count_G;
}

int AAStarNode::CalcHCount(const FVector & Goal)
{
	Count_H = FVector::Distance(Goal, GetActorLocation());
	return Count_H;
}

void AAStarNode::SetNearNodesPrevAsMe()
{
	for (auto it : NearNodes)
		it->PrevNode = this;
}


void AAStarNode::ResetAStarValue()
{
	bIsPath = false;
	bIsVisited = false;

	Count_F = 0;
	Count_G = 0;
	Count_H = 0;

	PrevNode.Get();
}

int AAStarNode::CalcFCount(const FVector & Start, const FVector & Goal)
{
	Count_F = CalcGCount(Start) + CalcHCount(Goal);
	return Count_F;
}
