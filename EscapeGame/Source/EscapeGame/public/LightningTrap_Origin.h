// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "LightningTrap_Origin.generated.h"

//�Ļ����� 4����. ����, ����, ����,����
//�浹�� ĸ�� ������Ʈ
//������ �������� tick time���� 0.1��
UCLASS()
class ESCAPEGAME_API ALightningTrap_Origin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightningTrap_Origin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
	UFUNCTION()
		void OnCharacterHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	bool IsActive();
protected:
	void initComponents();
	void loadAssets();
	void setRelativeCoordinates();
	void setupCollision();
	

	void turnOnTrap();
	void turnOffTrap();

	//�׼��� ���� Ÿ�̸�
	float Timer;
	
	
protected:
	
	UPROPERTY(VisibleAnywhere, Category = mesh)
		UStaticMeshComponent*MeshA;
	UPROPERTY(VisibleAnywhere, Category = mesh)
		UStaticMeshComponent*MeshB;
	UPROPERTY(VisibleAnywhere, Category = Collision)
		UCapsuleComponent*CapsuleCollision;
	UPROPERTY(VisibleAnywhere, Category = mesh)
		UParticleSystemComponent* Effect;
	UPROPERTY(VisibleAnywhere, Category = Contents)
		UAudioComponent* SparkAudio;
	//on, off ������ ����
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float IntervalTime;
	//effect�� �۵��ϴ� �ð�
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float ActveTime;
	UPROPERTY(EditInstanceOnly, Category = Contents)
		bool bIsActive;
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float Damage;
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float KnockBackRange;
	
};
