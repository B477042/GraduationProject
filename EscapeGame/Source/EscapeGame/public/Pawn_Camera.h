// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Pawn.h"



#include "Pawn_Camera.generated.h"


/*
	Dr.Joe를 촬영하는데만 이용될 pawn

*/
UCLASS()
class ESCAPEGAME_API APawn_Camera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawn_Camera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//대화하는 상대의 말을 듣게 된다
	void ListenTalk(TWeakObjectPtr<ACharacter> Talker);
	//말을 걸어오기 시작할 때 호출합니다
	void StartListenTo(TWeakObjectPtr<ACharacter>Talker);
private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* Cam;
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;

	TWeakObjectPtr<ACharacter>CurrentTalker;
};
