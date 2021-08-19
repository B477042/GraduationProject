// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ItemActor.h"
#include "Components/AudioComponent.h"
#include "Item_Recover.generated.h"

/**
 *	채력(베터리)를 회복시키는 아이템입니다
	닿으면 사라지고 인벤토리로 들어갑니다
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
	//아이템을 사용하면 출력될 소리를 다룬다
	UPROPERTY(VisibleAnywhere, Category = Content)
		UAudioComponent* Sound;
	UPROPERTY(VisibleAnywhere, Category = Content)
		UAudioComponent* PickupSound;

	//Effect를 재생할 때 쓰는 용도다. 이 위치로 접근해서 위치를 업데이트 시킨다
	UPROPERTY(VisibleAnywhere, Category = Content)
		TWeakObjectPtr<AActor>TargetActor;
};
