// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Actor.h"
#include "NPCCharacter.generated.h"

/*
	NPC Character Actor의 원형 클래스
	아무것도 안 해도 될거 같다

*/
UCLASS()
class ESCAPEGAME_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCCharacter();

	FString GetName() { return *Name; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	//UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	//	UAnimInstance* Anim;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "info", meta = (AllowPrivateAccess = "true"))
		FString Name;
};
