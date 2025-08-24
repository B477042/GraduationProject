// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility/Component_Mag.h"
#include "UnrealCore/SaveGame/EGSaveGame.h"
#include "EscapeGame.h"
#include "Actor/Weapon.h"
#include "Actor/SklillActor/GunnerBullet.h"
// Sets default values for this component's properties
UComponent_Mag::UComponent_Mag()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	MaxCapacity = 30;

	idxBullet = 0;
	SpawnBulletClass = AGunnerBullet::StaticClass();


	// ...
}


// Called when the game starts
void UComponent_Mag::BeginPlay()
{
	Super::BeginPlay();
	CreateMag();
	// ...
	auto OwnerActor = Cast<AWeapon>(GetOwner());
	if (!OwnerActor)
	{
		EGLOG(Error, TEXT("Casting failed"));
		return;
	}
	

	

}


void UComponent_Mag::nextBullet()
{
	++idxBullet;
	//������ �ʿ�
	if (idxBullet >= MaxCapacity)
	{
		idxBullet = 0;
	//	ReloadMag();
	}
	
	TopBullet = Mag[idxBullet];


}




void UComponent_Mag::SaveGame(UEGSaveGame * SaveInstance)
{
}

void UComponent_Mag::LoadGame(UEGSaveGame * LoadInstance)
{
}

void UComponent_Mag::CreateMag()
{
	if (Mag.Num()> 0)
	{
		EGLOG(Error, TEXT("Mag si already created"));
		return;
	}

	for(int i =0;i<MaxCapacity;++i)
	{
		Mag.Add(GetWorld()->SpawnActor<AGunnerBullet>(SpawnBulletClass));

	}

	TopBullet=Mag[0];
	idxBullet=0;
	EGLOG(Error, TEXT("Create"));
}



void UComponent_Mag::ReloadMag()
{
	
}

void UComponent_Mag::FireBullet(const FVector& FireLoation,const  FRotator& FireRotation, const FVector& FireFWVector)
{

	TopBullet->SetActorLocationAndRotation(FireLoation, FireRotation);

	TopBullet->ReadyToFire(FireFWVector, FireLoation, FireRotation);
	nextBullet();


}

void UComponent_Mag::ClearBullet()
{
	EGLOG(Error, TEXT("Clear Bullet"));
	if (Mag.Num() == 0)
	{
		return;
	}

	for (auto it : Mag)
	{
		if (it.IsValid())
		{
			it.Get()->Destroy();
			EGLOG(Log, TEXT("Destory"));
		}
	}
	Mag.Empty();
	TopBullet.Get();

}

