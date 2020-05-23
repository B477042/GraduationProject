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
	//�׾�� �� �� ȣ��ȴ�.
	//Stat�� hp 0 delegate�� �����Ұ� �ƴ϶� anim�� dead ����� ������ ������� �ؾ߰ڱ���
	
	//���ó�� �����۾�
	UFUNCTION()
		void ReadToDead();
	
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	UStatComponent_EGrunt* Stat;

	

	//Stat Component �����Ǹ� �ű⿡ �ִ´�. ���� Ž�� ����
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
		float AttackRange;
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
		FVector AttackExtent;

	float ATK;

};
