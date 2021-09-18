// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Weapon.generated.h"

/*

	BP에서 상속으로 무기를 제작해주는게 좋을거 같다

*/

UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
	Default=0,
	Rifle,
	Sniper,
	ShotGun,
	Rocket

};


UCLASS(Blueprintable)
class ESCAPEGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EWeaponTypes GetWeaponType()const { return WeaponType; }
	 


protected:

	UFUNCTION(BlueprintCallable)
		bool AttachMuzzleEffect();
	 

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MainBody;
 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VFX", meta = (AllowPrivateAccess = true))
		UParticleSystemComponent* VFX_Muzzle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SFX", meta = (AllowPrivateAccess = true))
		UAudioComponent* SFX_Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		ACharacter* OwnerChara;

	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<EWeaponTypes>WeaponType;
};
