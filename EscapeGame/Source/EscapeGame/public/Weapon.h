// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Component_Mag.h"
#include "Weapon.generated.h"

/*
*	*AWeapon
*	Gunner들이 사용하는 Weapon들의 공용 클래스
*	자식 클래스로 BP를 활용할 것
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
	virtual void BeginDestroy()override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents()override;

	FVector CalcFireDirection(const FVector& TargetLocation);
	FRotator CalcRotationForBullet(const FVector& FireDirection);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DiscardWeapon();


	void AttachedBy(class ACharacter* OtherCharacter);
	//Return True If This Weapon can fire a bullet
	bool Attack(const FVector& TargetLocation);
	



protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = true))
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		USkeletalMeshComponent* MainBody;
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, meta = (AllowPrivateAccess = true))
		UComponent_Mag* Mag;

	UPROPERTY(VisibleInstanceOnly, Category = Anim, Meta = (AllowPrivateAccess = true))
		class UAnim_Weapon* Anim;
	
	
	/*
	* Fire Controll
	*/
	
	//FireRate
	float RPM;
	//If Ture Ejecting is on progress. Can't Fire
	bool bIsEjcting;
	const FName Name_Muzzle = TEXT("Muzzle");

	// 발사 지점에서 원까지 거리 
	float FireControl_DistanceOffset;
	//원 지름
	float FireControl_Radius;
 
	

	//UPROPERTY(BlueprintReadOnly)
	//	TEnumAsByte<EWeaponTypes>WeaponType;


};
