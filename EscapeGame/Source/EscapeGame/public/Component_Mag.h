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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//총알들의 위치 정보, 상태 저장. Mag 상태 저장 / Owner가 호출한다
	void SaveGame(class UEGSaveGame* SaveInstance);
	//총알들의 위치 정보, 상태 불러오기 Mag 상태 불러오기/ Owner가 호출한다
	void LoadGame(class UEGSaveGame* LoadInstance);

	void CreateMag();
	void UseBullet();
	void ReloadMag();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TArray<TSoftObjectPtr<AGunnerBullet>> Mag;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSoftObjectPtr<AGunnerBullet> TopBullet;
	int idxBullet;
	int MaxCapacity;
};
