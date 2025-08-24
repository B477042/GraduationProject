// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"


class UMiniMapMarkerComponent;

UCLASS()
class ESCAPEGAME_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Character���� �ֿ�����
	virtual void BePickedUp(ACharacter* OtherActor);
	virtual void PostInitializeComponents()override;
	

	//�ڽĵ鿡�� tag�� �ݵ�� ��������� �ȴ�. 
	 virtual  FName GetTag()PURE_VIRTUAL(AItemActor::GetTag,return TEXT("Default") ;);
	//Use This Item
	virtual void UseMe(ACharacter* UserActor) PURE_VIRTUAL(AItemActor::UseMe, ;);
	//Collision->off, hidden in game	
	void SetItemDisable();



protected:
	UFUNCTION()
	void SaveGame(class UEGSaveGame* SaveInstance);
	UFUNCTION()
	void LoadGame(const class UEGSaveGame* LoadInstance);

	





protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UParticleSystemComponent* Effect;
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UMiniMapMarkerComponent* MiniMapMarker;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USceneComponent* Root;
	//�� �������� ������ �ִ� ����
	UPROPERTY(VisibleAnywhere)
		ACharacter* OwnerActor;
	//�������� Player�� �ֿ� ���, ��ȿ���� �ʰ� �ȴ�
	UPROPERTY(VisibleAnywhere)
		bool bIsItemVaild;
	
	
	
};
