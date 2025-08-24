// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealCore/EGPlayerState.h"

#include "Actor/Character/EGPlayerController.h"
#include "GameAbility/GameAbilitySystem/AttributeSet/EGCharacterAttributeSet.h"

#define IMPLEMENT_ATTRIBUTE_GETTER(PropertyName) \
	float AEGPlayerState::Get##PropertyName()const\
	{\
		return PlayerAttributeSet->Get##PropertyName(); \
	}

#define BIND_ATTRIBUTE_CHANGED_EVENT(PropertyName) \
	On##PropertyName##ChanegedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->Get##PropertyName##Attribute()).AddUObject(this,&AEGPlayerState::On##PropertyName##Changed);

#define UNBIND_ATTRIBUTE_CHANGED_EVENT(PropertyName) \
	On##PropertyName##ChanegedDelegateHandle.Reset();

IMPLEMENT_ATTRIBUTE_GETTER(AttackPoint)
IMPLEMENT_ATTRIBUTE_GETTER(Level)
IMPLEMENT_ATTRIBUTE_GETTER(ExpPoint)
IMPLEMENT_ATTRIBUTE_GETTER(ExpBounty)
IMPLEMENT_ATTRIBUTE_GETTER(ManaPoint)
IMPLEMENT_ATTRIBUTE_GETTER(MaxManaPoint)
IMPLEMENT_ATTRIBUTE_GETTER(StaminaPoint)
IMPLEMENT_ATTRIBUTE_GETTER(MaxStaminaPoint)

AEGPlayerState::AEGPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	PlayerAttributeSet = CreateDefaultSubobject<UEGCharacterAttributeSet>(TEXT("PlayerAttributeSet"));
	SetNetUpdateFrequency(100.f);
	
}

void AEGPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// Bind Attribute Changed
	BIND_ATTRIBUTE_CHANGED_EVENT(AttackPoint)
	BIND_ATTRIBUTE_CHANGED_EVENT(Level)
	BIND_ATTRIBUTE_CHANGED_EVENT(ExpPoint)
	BIND_ATTRIBUTE_CHANGED_EVENT(ExpBounty)
	BIND_ATTRIBUTE_CHANGED_EVENT(ManaPoint)
	BIND_ATTRIBUTE_CHANGED_EVENT(MaxManaPoint)
	

	
}


TObjectPtr<AEGPlayerController> AEGPlayerState::getEGPlayerController()
{
	return Cast<AEGPlayerController>(GetOwner());
	
}

void AEGPlayerState::OnAttackPointChanged(const FOnAttributeChangeData& Data)
{
}

void AEGPlayerState::OnLevelChanged(const FOnAttributeChangeData& Data)
{
}

void AEGPlayerState::OnExpPointChanged(const FOnAttributeChangeData& Data)
{
}

void AEGPlayerState::OnExpBountyChanged(const FOnAttributeChangeData& Data)
{
}

void AEGPlayerState::OnManaPointChanged(const FOnAttributeChangeData& Data)
{
}

void AEGPlayerState::OnMaxManaPointChanged(const FOnAttributeChangeData& Data)
{
}

void AEGPlayerState::OnStaminaPointChanged(const FOnAttributeChangeData& Data)
{
}

void AEGPlayerState::OnMaxStaminaPointChanged(const FOnAttributeChangeData& Data)
{
}

void AEGPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UNBIND_ATTRIBUTE_CHANGED_EVENT(AttackPoint)
	UNBIND_ATTRIBUTE_CHANGED_EVENT(Level)
	UNBIND_ATTRIBUTE_CHANGED_EVENT(ExpPoint)
	UNBIND_ATTRIBUTE_CHANGED_EVENT(ExpBounty)
	UNBIND_ATTRIBUTE_CHANGED_EVENT(ManaPoint)
	UNBIND_ATTRIBUTE_CHANGED_EVENT(MaxManaPoint)
	
}
