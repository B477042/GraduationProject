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

protected:
	//상속 받은 함수들
	bool Activate()override;
	bool DeActivate()override;
	void ClearTrap()override;
	void SettingTrap()override;

private:
	void LoadAssets();
	void SetRelativeCoordinates();
	
};
