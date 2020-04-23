// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Pawn.h"



#include "Pawn_Camera.generated.h"


/*
	Dr.Joe�� �Կ��ϴµ��� �̿�� pawn

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
	//��ȭ�ϴ� ����� ���� ��� �ȴ�
	void ListenTalk(TWeakObjectPtr<ACharacter> Talker);
	//���� �ɾ���� ������ �� ȣ���մϴ�
	void StartListenTo(TWeakObjectPtr<ACharacter>Talker);
private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* Cam;
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;

	TWeakObjectPtr<ACharacter>CurrentTalker;
};
