// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "EnemyCharacter.h"
#include "Anim_Grunt.h"
#include "StatComponent_EGrunt.h"
#include "GruntCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API AGruntCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AGruntCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attack()override;


	const static float MaxWalkingSpeed;
	const static float MaxRunningSpeed;
	const static float MinWalkingSpeed;

	
	UFUNCTION(BlueprintCallable)
		float DropExp() { return Stat->GetDropExp(); }

private:
	//죽어야 될 때 호출된다.
	//Stat의 hp 0 delegate에 연동할게 아니라 anim의 dead 모션이 끝나면 사라지게 해야겠구나
	
	//사망처리 사전작업
	UFUNCTION()
		void ReadToDead();
	
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	UStatComponent_EGrunt* Stat;

	

	//Stat Component 정리되면 거기에 넣는다. 전방 탐지 범위
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
		float AttackRange;
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
		FVector AttackExtent;

	float ATK;

};
