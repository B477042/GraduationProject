// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

/*

������ �߰��� ��� �������� ���� Ŭ������ ���� ��

��� PROPERTY
Staticemesh
particle

��� Function
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
	//������ �۵�, default return value false
	virtual void ActivateTrap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult) PURE_VIRTUAL(ATrap::ActivateTrap, ;);
	//������ ����� ����, default return value false
	virtual void DeActivateTrap() PURE_VIRTUAL(ATrap::DeActivateTrap, ;);
	//�۵��� ������ ����
	virtual void ClearTrap() PURE_VIRTUAL(ATrap::ClearTrap, ;);
	//������ spawn ���� �� ���� �Ǿ��� �͵�
	virtual void SettingTrap()  PURE_VIRTUAL(ATrap::SettingTrap, ;);
protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UParticleSystemComponent* Effect;


};
