// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StatComponent.h"
#include "StatComponent_Enemy.generated.h"

/**
 * 
 */
struct FEnemyData;

UCLASS()
class ESCAPEGAME_API UStatComponent_Enemy : public UStatComponent
{
	GENERATED_BODY()
public:
	UStatComponent_Enemy();

	virtual void InitializeComponent()override;

	//�ڽ� Ŭ�������� ����ϰ� �� ���̴�. ������ Owner class actor�� �ϰ� �� ���̴�
	virtual void SaveGame(FEnemyData* SaveData);
	
	virtual void LoadGame(const FEnemyData* LoadData);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 GetDropExp();
	
	int32 GetType() const { return Type; }

	//Set Type value as input value
	void SetType(int32 input);



protected:
	

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 DropExp;
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
		int32 Type;
};
