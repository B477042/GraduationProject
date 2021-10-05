// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Fury.h"
#include "Sound/SoundWave.h"

// Sets default values for this component's properties
UComponent_Fury::UComponent_Fury()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USoundWave>SW(TEXT("SoundWave'/Game/ParagonKwang/Characters/Heroes/Kwang/Sounds/SoundWaves/Kwang_Ability_Ultimate_Ready_020.Kwang_Ability_Ultimate_Ready_020'"));
	if (SW.Succeeded())
	{
		SFX_FuryMax = SW.Object;
		
	}

	// ...
}


float UComponent_Fury::GetFury() const
{
	return Fury;
}

void UComponent_Fury::LoadFury(const float& NewFury)
{
	Fury = NewFury;
	if (OnFuryChanged.IsBound())
	{
		OnFuryChanged.Execute(GetFuryRatio());
	}
}

void UComponent_Fury::BeginDestroy()
{
	Super::BeginDestroy();
	if (OnFuryChanged.IsBound())
	{
		OnFuryChanged.Unbind();
	}
}

// Called when the game starts
void UComponent_Fury::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComponent_Fury::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UComponent_Fury::TakeDamage(const float NewDamage)
{
	if (Fury == MaximumFury)
	{
		return Fury;
	}


	Fury += NewDamage*2.3f;
	



	if (Fury >= MaximumFury)
	{
		Fury = MaximumFury;
		
		//Notify Fury is full
		UGameplayStatics::PlaySound2D(this, SFX_FuryMax);

	}
	//Notify Fury changed
	if (OnFuryChanged.IsBound())
	{
		OnFuryChanged.Execute(GetFuryRatio());
	}


	return Fury;
}

bool  UComponent_Fury::UseFury()
{
	if (GetFuryRatio() < 1.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("Not enough fury"));
		return false;
	}
	Fury = 0.0f;
	if (OnFuryChanged.IsBound())
	{
		OnFuryChanged.Execute(GetFuryRatio());
	}

	return true;
}

