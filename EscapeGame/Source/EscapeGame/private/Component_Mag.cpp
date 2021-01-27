// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Mag.h"
#include "EGSaveGame.h"


// Sets default values for this component's properties
UComponent_Mag::UComponent_Mag()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxCapacity = 40;

	idxBullet = 0;



	// ...
}


// Called when the game starts
void UComponent_Mag::BeginPlay()
{
	Super::BeginPlay();
	CreateMag();
	// ...

	

}

void UComponent_Mag::nextBullet()
{
	++idxBullet;
	//재장전 필요
	if (idxBullet <= MaxCapacity)
	{
		idxBullet = 0;

	}
	TopBullet = Mag[idxBullet];


}


// Called every frame
void UComponent_Mag::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
		Mag.Add(GetWorld()->SpawnActor<AGunnerBullet>());

	}

	TopBullet=Mag[0];
	idxBullet=0;

}

void UComponent_Mag::UseBullet()
{


	nextBullet();
}

void UComponent_Mag::ReloadMag()
{

}

