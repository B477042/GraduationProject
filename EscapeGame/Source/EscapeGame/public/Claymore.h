// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Trap.h"
#include "Claymore.generated.h"

/**
 * Claymore�� �̿��� ����
	Player�� �ٰ����� ������ �Ѵ�
	�׽�Ʈ�� ���� fŰ�� ������ ��Ʈ������
	
	2019 10 13 fŰ ���ε�������

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
	//��� ���� �Լ���
	bool Activate()override;
	bool DeActivate()override;
	void ClearTrap()override;
	void SettingTrap()override;

private:
	void LoadAssets();
	void SetRelativeCoordinates();
	
};
