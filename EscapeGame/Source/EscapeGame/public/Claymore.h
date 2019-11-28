// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Trap.h"
#include"EGPlayerCharacter.h"
#include "Claymore.generated.h"

/**
 * Claymore�� �̿��� ����
	Player�� �ٰ����� ������ �Ѵ�
	
	Ÿ�̸Ӵ� 0.5�� �̳���
	�ݰ��� �ִ� �������� �ִ� �ݰ��� 5����
	�ִ� ������ 10���ͷ�
	
	

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
	//��� ���� �Լ���
	void ActivateTrap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult)override;
	void DeActivateTrap()override;
	void ClearTrap()override;
	void SettingTrap()override;

private:
	void loadAssets();
	void setRelativeCoordinates();
	void setupCollision();
	void activeTimer();
	void explosion();
	FVector getNormalVectorDistance();
	float getDistance();
	float getDamage();
	//float get
private:
	const float maxDamageRange=5.0f;
	const float minDamageRange = 10.0f;
	

	TWeakObjectPtr<AEGPlayerCharacter> target;
private:
	UPROPERTY(VisibleAnywhere, Category = Collision)
		UBoxComponent*BoxCollision;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float MinDamage;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float MaxDamage;
	UPROPERTY(EditInstanceOnly, Category = Content)
		float Timer;
	UPROPERTY(EditInstanceOnly, Category = Statue)
		bool isActive;
	
};
