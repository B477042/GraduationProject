// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "SmokeTrap.generated.h"


/*
	������ ����
	���Ⱑ �ϳ��� �� ������ �ʾƼ� 4���� �д�
	���� 5���� ������ �ϰ� �ݸ������� �浹�� ó���Ѵ�. 
	root��  ��� ����� �Ѵ�.


	������ �������� �ް� ���� �ð��� �ڳ��� �� �������� ������.

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
