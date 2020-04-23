// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "NPCCharacter.generated.h"

/*
	NPC Character Actor�� ���� Ŭ����
	�ƹ��͵� �� �ص� �ɰ� ����

*/
UCLASS()
class ESCAPEGAME_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	string GetName() { return name; }
protected:
	/*UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		UAnimInstance* Anim;*/
	string name;
};
