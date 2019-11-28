// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

/*

앞으로 추가될 모든 함정들의 원형 클래스로 만들 것

상속 PROPERTY
Staticemesh
particle

상속 Function
Activate
DeActivate
ClearTrap
SettingTrap

*/

UCLASS(abstract)
class ESCAPEGAME_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
protected:
	//함정을 작동, default return value false
	virtual void ActivateTrap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult) PURE_VIRTUAL(ATrap::ActivateTrap, ;);
	//함정의 기능을 정지, default return value false
	virtual void DeActivateTrap() PURE_VIRTUAL(ATrap::DeActivateTrap, ;);
	//작동한 함정을 정리
	virtual void ClearTrap() PURE_VIRTUAL(ATrap::ClearTrap, ;);
	//함정이 spawn 됐을 때 셋팅 되야할 것들
	virtual void SettingTrap()  PURE_VIRTUAL(ATrap::SettingTrap, ;);
protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UParticleSystemComponent* Effect;


};
