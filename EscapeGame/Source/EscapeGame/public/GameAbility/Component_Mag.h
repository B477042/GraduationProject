// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Component_Mag.generated.h"


class AGunnerBullet;

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


	//�Ѿ˵��� ��ġ ����, ���� ����. Mag ���� ���� / Owner�� ȣ���Ѵ�
	void SaveGame(class UEGSaveGame* SaveInstance);
	//�Ѿ˵��� ��ġ ����, ���� �ҷ����� Mag ���� �ҷ�����/ Owner�� ȣ���Ѵ�
	void LoadGame(class UEGSaveGame* LoadInstance);

	void CreateMag();
	
	void ReloadMag();
	void FireBullet(const FVector& FireLocation, const FRotator& FireRotation,const FVector& FireFWVector);
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
