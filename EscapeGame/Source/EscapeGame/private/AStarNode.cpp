// Fill out your copyright notice in the Description page of Project Settings.

#include "AstarNode.h"
#include "EGPlayerCharacter.h"
#include "AstarFinder.h"
#include "Item_CardKey.h"
#include "Engine.h"
#include "EGGameInstance.h"

// Sets default values
AAstarNode::AAstarNode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	initComponents();
	bIsPath = false;
	bIsVisited = false;
	bIsKeyNode = false;

	Count_F = 0;
	Count_G = 0;
	Count_H = 0;

}

// Called when the game starts or when spawned
void AAstarNode::BeginPlay()
{
	Super::BeginPlay();

	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)return;

	auto finder = GameInstance->GetAStarFinder();
	if (finder==nullptr) {
		EGLOG(Error, TEXT("Can't find finder"));
		return;
	}

	finder->AddNode(this);

	if (bIsGoalNode)
	{
		finder->SetGoalPoint(this);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Goal Node : %s"),*GetName());
	}
	if (bIsKeyNode)
	{
		finder->SetKeyPoint(this);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Key Node : %s"),*GetName());
	}
	Deactivate();
	//UAstarComponent::A_AstarNodes.Add(this);

}

void AAstarNode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AAstarNode::OnActorOverlap);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AAstarNode::OnActorOverlapEnd);
	
	
	//OnPlayerEnter.AddUObject(this, &AAStarFinder::GetInstance()->StartPathFinder);
}

void AAstarNode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)return;

	auto finder = GameInstance->GetAStarFinder();
	if (finder == nullptr) {
		EGLOG(Error, TEXT("Can't find finder"));
		return;
	}



	finder->ClearNodes();
	EGLOG(Error, TEXT("End Play"));
}

void AAstarNode::OnActorOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OnPlayerEnter.Broadcast(this);
	
	auto player = Cast<AEGPlayerCharacter>(OtherActor);
	if (!player)return;

	EPathTarget Mode;
	//열쇠가 있다면 문으로 안내
	if (player->Inventory->HasItem(AItem_CardKey::Tag))
		Mode = EPathTarget::Gate;
	else
		Mode = EPathTarget::Key;
	
	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)return;

	auto finder = GameInstance->GetAStarFinder();
	if (finder == nullptr) {
		EGLOG(Error, TEXT("Can't find finder"));
		return;
	}


	finder->StartPathFinder(this,Mode);


}

void AAstarNode::OnActorOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)return;

	auto finder = GameInstance->GetAStarFinder();
	if (finder == nullptr) {
		EGLOG(Error, TEXT("Can't find finder"));
		return;
	}
	finder-> ResetResult();
}

// Called every frame
void AAstarNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AAstarNode::operator<(const AAstarNode & lhs)
{

	return Count_F<lhs.Count_F;
}

//bool AAstarNode::operator<(const AAstarNode & lhs, const AAstarNode & rhs)
//{
//	return lhs.Count_F<rhs.Count_F;
//}



bool AAstarNode::operator>(const AAstarNode & lhs)
{
	return Count_F > lhs.Count_F;
}

bool AAstarNode::operator==(const AAstarNode & lhs)
{
	return  Count_F == lhs.Count_F;
}

void AAstarNode::SortNearNodes()
{
	
	


}



void AAstarNode::Activate()
{
	BodyMesh->SetHiddenInGame(false);
}

void AAstarNode::Deactivate()
{
	BodyMesh->SetHiddenInGame(true);
}

void AAstarNode::SetRoad(bool bResult)
{
	bIsPath = bResult;
}






void AAstarNode::initComponents()
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

int AAstarNode::CalcGCount(const FVector & Start)
{
	Count_G = FVector::Distance(Start, GetActorLocation());
	return Count_G;
}

int AAstarNode::CalcHCount(const FVector & Goal)
{
	Count_H = FVector::Distance(Goal, GetActorLocation());
	return Count_H;
}

void AAstarNode::SetNearNodesPrevAsMe()
{
	for (auto it : NearNodes)
	{
		//it가 유효하고
		if (!it.IsValid())continue;
		//방문하지 않은 노드여야 한다
		if(!it->bIsVisited)
		it->PrevNode = this;
	}
}


void AAstarNode::ResetAStarValue()
{
	bIsPath = false;
	bIsVisited = false;

	Count_F = 0;
	Count_G = 0;
	Count_H = 0;

	PrevNode=nullptr;
}

int AAstarNode::CalcFCount(const FVector & Start, const FVector & Goal)
{
	Count_F = CalcGCount(Start) + CalcHCount(Goal);
	return Count_F;
}
