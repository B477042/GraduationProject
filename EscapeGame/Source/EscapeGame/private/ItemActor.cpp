// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemActor.h"
#include "EGSaveGame.h"
#include "EGGameInstance.h"



// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	//BoxCollision->SetCollisionProfileName(FName("OnTrapTrigger"));

	RootComponent = Body;
	//Effect->SetupAttachment(RootComponent);
	//Body->SetupAttachment(RootComponent);
	bIsItemVaild = true;
	OwnerActor = nullptr;
	Tags.Add(TItem);
}



// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bIsItemVaild)
		SetItemDisable();

	//EGLOG(Error, TEXT("This Item Name : %s"), *GetName());
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::BePickedUp(ACharacter * OtherActor)
{
	OwnerActor = OtherActor;
	
}

void AItemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnPlayerOverlap);

	auto GameInstance = Cast<UEGGameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		EGLOG(Error, TEXT("Game Instance is not UEGGameInstance"));
		return;
	}
	GameInstance->OnSaveGamePhaseDelegate.AddDynamic(this,&AItemActor::SaveGame);
	GameInstance->OnLoadGamePhaseDelegate.AddDynamic(this, &AItemActor::LoadGame);
	//EGLOG(Error, TEXT("post init"));
}

//FName AItemActor::GetTag()
//{
//	return Tag;
//}

void  AItemActor::SetItemDisable()
{
	Body->SetCollisionProfileName("NoCollision");
	SetActorHiddenInGame(true);
	
}



/*
	2020 11 07
	����� �����۵� : ���忡 ��ġ�� ������
	����Ǽ� �ȵ� �����۵� : �÷��̾ �ε��� �� ���� ������
	-> Tag�� �з� Item. 
	https://docs.unrealengine.com/ko/Gameplay/Tags/index.html
	Tag ����
*/
void AItemActor::SaveGame(UEGSaveGame * SaveInstance)
{
	if (!SaveInstance)
	{
		EGLOG(Error, TEXT("SaveInstance is null"));
		return;
	}
	//Tag�߿� �������� ������ �������� �ʴ´�
	if (Tags.Contains(TSpawned))
	{
		EGLOG(Error, TEXT("%s can't store data. Contain Tag - Spawned"),*GetName());
		return;
	}

	//Map�� ��ϵ��� �ʾƾ� �ȴ�
	if (!SaveInstance->D_Items.Contains(GetName()))
	{
		FItemData ItemData;

		ItemData.Location = GetActorLocation();
		ItemData.Rotation = GetActorRotation();
		ItemData.bIsVaild = bIsItemVaild;
		SaveInstance->D_Items.Add(GetName(), ItemData);
		EGLOG(Error, TEXT("Item Saved : %s"), *GetName());
	}
	else
		EGLOG(Error, TEXT("%s is already included in D_Items"));
	

	//EGLOG(Error, TEXT("Save Game func end"));
}

void AItemActor::LoadGame(const UEGSaveGame * LoadInstance)
{
	if (!LoadInstance)
	{
		EGLOG(Error, TEXT("LoadInstance is null"));
		return ;
	}
	auto LoadData = LoadInstance->D_Items.Find(GetName());
	if (!LoadData)
	{
		EGLOG(Error, TEXT("Load Item Failed, %s"), *GetName());
		return;
	}
	SetActorLocationAndRotation(LoadData->Location, LoadData->Rotation);
	bIsItemVaild = LoadData->bIsVaild;
	
	//��ȿ���� �ʴ� �������̶�� ����ó��
	if (!bIsItemVaild)
		SetItemDisable();
}


