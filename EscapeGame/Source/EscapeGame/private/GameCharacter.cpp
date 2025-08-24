// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/GameCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Component/EGCharacterMovementComponent.h"
// Sets default values
AGameCharacterBase::AGameCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UEGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//init Gas
	// AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	// AbilitySystemComponent->SetIsReplicated(true);
	// AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	//AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("AttributeSet"));
	
}

// Called when the game starts or when spawned
void AGameCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGameCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	EGLOG(Log,TEXT("%s -possessed-> %s"),*NewController->GetName(),*GetName());
	{
		
	}
	
}

void AGameCharacterBase::SetAbilitySystemComponent(TObjectPtr<UAbilitySystemComponent> NewAbilitySystemComponent)
{
	if (!AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent = NewAbilitySystemComponent;
	}
	else
	{
	}
}

void AGameCharacterBase::SetAttributeSet(TObjectPtr<UEGCharacterAttributeSet> AttributeSet)
{
	if (!CharacterAttributeSet.IsValid())
	{
		CharacterAttributeSet = AttributeSet;
	}
	else
	{
	}
}

