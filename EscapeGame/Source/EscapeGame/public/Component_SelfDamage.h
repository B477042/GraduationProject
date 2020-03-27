// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "Component_SelfDamage.generated.h"

/*
	Owner에게 일정 시간마다 데미지를 입히는 컴포넌트입니다

*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UComponent_SelfDamage : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_SelfDamage();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//ActTimer가 LimitTime에 도달하면 이 만큼의 데미지를 Owner에게 입힌다
	UPROPERTY(EditInstanceOnly, Category = "Damage")
		float Damage;
	//이 컴포넌트의 Owner
	UPROPERTY(EditInstanceOnly, Category = "Damage")
		ACharacter* Owner;
	//이 수치만큼 Timer가 제한된다
	UPROPERTY(VisibleInstanceOnly, Category = "Damage")
		float LimitTime;
	//Timer 변수
	UPROPERTY(VisibleInstanceOnly, Category = "Damage")
		float ActTimer;
};
