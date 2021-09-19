// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Weapon.generated.h"

/*
*	*AWeapon
*	Gunner���� ����ϴ� Weapon���� ���� Ŭ����
*	�ڽ� Ŭ������ BP�� Ȱ���� ��
*	
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

USTRUCT(BlueprintType)
struct FBulletTypeData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		float Acceleration;


};


UCLASS(Abstract, Blueprintable)
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
	 
	void AttachedBy(class ACharacter* OtherCharacter);




protected:

	 

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = true))
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* MainBody;

	UPROPERTY(VisibleInstanceOnly, Category = Anim, Meta = (AllowPrivateAccess = true))
		class UAnim_Weapon* Anim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<class ACharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<EWeaponTypes>WeaponType;
};
