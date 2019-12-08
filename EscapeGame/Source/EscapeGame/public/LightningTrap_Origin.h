// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "LightningTrap_Origin.generated.h"

//파생형은 4가지. 가로, 세로, 상향,하향
//충돌은 캡슐 컴포넌트
//데미지 프레임은 tick time마다 0.1씩
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

	//액션을 위한 타이머
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
	//on, off 사이의 간격
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float IntervalTime;
	//effect가 작동하는 시간
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float ActveTime;
	UPROPERTY(EditInstanceOnly, Category = Contents)
		bool bIsActive;
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float Damage;
	UPROPERTY(EditInstanceOnly, Category = Contents)
		float KnockBackRange;
	
};
