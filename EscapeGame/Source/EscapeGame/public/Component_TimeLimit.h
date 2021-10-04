// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "Component_TimeLimit.generated.h"

DECLARE_DELEGATE(FOnTimeOver);

UCLASS(ClassGroup = "Custom", Config = "GameComponent", meta = (BlueprintSpawnableComponent))
class ESCAPEGAME_API UComponent_TimeLimit : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_TimeLimit();

	void TimeExtend(const float& AddTime);
	float GetCurrentRemainTime()const;
	void LoadTime(float NewTime);
	void SetTimerActive(bool bResult);
	virtual void BeginDestroy()override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FOnTimeOver OnTimeOver;
protected:
	UPROPERTY(BlueprintReadOnly, Config, VisibleAnywhere, meta = (AllowPrivateAccess = true))
		float RemainTime;


};
