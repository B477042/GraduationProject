// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_SelfDamage.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values for this component's properties
UComponent_SelfDamage::UComponent_SelfDamage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	Damage = 10.0f;
	LimitTime = 2.0f;
	ActTimer = 0.0f;
}


// Called when the game starts
void UComponent_SelfDamage::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = Cast<ACharacter>(GetOwner());
	if (Owner == nullptr)
	{
		EGLOG(Error, TEXT("This Component's Owner is null"));
	}
}


// Called every frame
void UComponent_SelfDamage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	ActTimer += DeltaTime;
	if (ActTimer >= LimitTime)
	{
		ActTimer = 0.0f;
		FDamageEvent DamageEvent;
		Owner->TakeDamage(Damage,DamageEvent,Owner->GetController(),Owner );
	}

	//UKismetMathLibrary::lerp


}

