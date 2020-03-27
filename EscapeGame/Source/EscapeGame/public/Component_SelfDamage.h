// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "Component_SelfDamage.generated.h"

/*
	Owner���� ���� �ð����� �������� ������ ������Ʈ�Դϴ�

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
	//ActTimer�� LimitTime�� �����ϸ� �� ��ŭ�� �������� Owner���� ������
	UPROPERTY(EditInstanceOnly, Category = "Damage")
		float Damage;
	//�� ������Ʈ�� Owner
	UPROPERTY(EditInstanceOnly, Category = "Damage")
		ACharacter* Owner;
	//�� ��ġ��ŭ Timer�� ���ѵȴ�
	UPROPERTY(VisibleInstanceOnly, Category = "Damage")
		float LimitTime;
	//Timer ����
	UPROPERTY(VisibleInstanceOnly, Category = "Damage")
		float ActTimer;
};
