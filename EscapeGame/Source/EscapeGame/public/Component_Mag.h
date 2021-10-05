// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GunnerBullet.h"
#include "Components/ActorComponent.h"
#include "Component_Mag.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UComponent_Mag : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Mag();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void nextBullet();



public:	


	//총알들의 위치 정보, 상태 저장. Mag 상태 저장 / Owner가 호출한다
	void SaveGame(class UEGSaveGame* SaveInstance);
	//총알들의 위치 정보, 상태 불러오기 Mag 상태 불러오기/ Owner가 호출한다
	void LoadGame(class UEGSaveGame* LoadInstance);

	void CreateMag();
	
	void ReloadMag();
	void FireBullet(const FVector& FireLoation, const FRotator& FireRotation,const FVector& FireFWVector);
	void ClearBullet();


	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TArray<TSoftObjectPtr<AGunnerBullet>> Mag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSoftObjectPtr<AGunnerBullet> TopBullet;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,  meta = (AllowPrivateAccess = true))
		TSubclassOf<AGunnerBullet>SpawnBulletClass;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int idxBullet;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int MaxCapacity;

};
