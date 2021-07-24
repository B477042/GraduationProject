// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ItemActor.h"
#include "Components/AudioComponent.h"
#include "Item_Recover.generated.h"

/**
 *	ä��(���͸�)�� ȸ����Ű�� �������Դϴ�
	������ ������� �κ��丮�� ���ϴ�
 */
UCLASS()
class ESCAPEGAME_API AItem_Recover : public AItemActor
{
	GENERATED_BODY()

public:

	AItem_Recover();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BePickedUp(ACharacter* OtherActor)override;
	virtual void PostInitializeComponents()override;
	virtual void UseMe(ACharacter* UserActor)override;
	virtual FName GetTag()override;
	static const FName Tag;
protected:

	UFUNCTION(BlueprintCallable)
	 void OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	void loadAsset();
	UFUNCTION()
	void turnOffEffect();
private:
	//if true, this actor hide from world
	   
	UPROPERTY(VisibleAnywhere)
	int amount_Recovery;
	//�������� ����ϸ� ��µ� �Ҹ��� �ٷ��
	UPROPERTY(VisibleAnywhere, Category = Content)
		UAudioComponent* Sound;
	UPROPERTY(VisibleAnywhere, Category = Content)
		UAudioComponent* PickupSound;

	//Effect�� ����� �� ���� �뵵��. �� ��ġ�� �����ؼ� ��ġ�� ������Ʈ ��Ų��
	UPROPERTY(VisibleAnywhere, Category = Content)
		TWeakObjectPtr<AActor>TargetActor;
};
