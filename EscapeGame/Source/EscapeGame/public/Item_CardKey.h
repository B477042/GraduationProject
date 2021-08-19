// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "ItemActor.h"
#include "Item_CardKey.generated.h"

/**
 *	문을 열 수 있는 카드키 아이템
 */
UCLASS()
class ESCAPEGAME_API AItem_CardKey : public AItemActor
{
	GENERATED_BODY()
public:
	AItem_CardKey();
	FName GetTag();
	void UseMe(ACharacter* UserActor);

	virtual void PostInitializeComponents()override;
	virtual void BePickedUp(ACharacter* OtherActor);
	const static FName Tag;
protected:

	void loadAssets();
private:

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UPROPERTY(BlueprintReadWrite, Category = "SoundEffect", meta = (AllowPrivateAccess = "true"))
		UAudioComponent* Sound;
	UPROPERTY(EditAnywhere, Category = "DetectCollision")
		UBoxComponent* DetectCollision;
};
