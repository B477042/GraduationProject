// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "SmokeTrap.generated.h"


/*
	연기형 함정
	연기가 하나면 잘 보이지 않아서 4개를 둔다
	연기 5개로 연출을 하고 콜리전으로 충돌을 처리한다. 
	root는  가운데 연기로 한다.


	들어오면 데미지를 받고 일정 시간이 자나면 또 데미지를 입힌다.

*/
UCLASS()
class ESCAPEGAME_API ASmokeTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmokeTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	const float ReActTimer = 0.5f;
private:
	UFUNCTION()
		void OnCharacterEntered(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);
private:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UBoxComponent* Collision;
	UPROPERTY(VisibleAnywhere, Category = Particle)
		TArray<UParticleSystemComponent*> Effects;
	UPROPERTY(VisibleAnywhere, Category = Damage)
		float Damage;
	UPROPERTY(VisibleAnywhere, Category = Timer)
		float Timer;
	UPROPERTY(VisibleAnywhere, Category = Particle)
		const int n_Smokes=4;

};
