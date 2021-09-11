// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "Component_Fury.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnFuryChanged, float,Ratio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UComponent_Fury : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Fury();
	//Called When Fury value changed
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Delegate")
	FOnFuryChanged OnFuryChanged;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float TakeDamage(const float NewDamage);
	float GetFuryRatio() { return Fury / MaximumFury; }
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Value", meta = (AllowPrivateAccess = true, UIMax = 0.00, UIMin = 100.00))
	float Fury=0.0f; 
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Value", meta = (AllowPrivateAccess = true, UIMax = 0.00, UIMin = 100.00))
	float MaximumFury = 100.0f;
	
	
		
};
