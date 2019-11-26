// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Trap.h"
#include "Claymore.generated.h"

/**
 * Claymore를 이용한 함정
	Player가 다가가면 터지게 한다
	테스트를 위해 f키를 누르면 터트려본다
	
	2019 10 13 f키 바인딩까지만

 */
UCLASS()
class ESCAPEGAME_API AClaymore : public ATrap
{
	GENERATED_BODY()
public:
	AClaymore();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents()override;

protected:
	//상속 받은 함수들
	void ActivateTrap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult)override;
	void DeActivateTrap()override;
	void ClearTrap()override;
	void SettingTrap()override;

private:
	void loadAssets();
	void setRelativeCoordinates();
	void setupCollision();
	void activeTimer();
	
private:
	UPROPERTY(VisibleAnywhere, Category = Collision)
		UBoxComponent*BoxCollision;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float Damage;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float Timer;
};
