// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "NPCCharacter.h"
#include "NPC_DrJoe.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPEGAME_API ANPC_DrJoe : public ANPCCharacter
{
	GENERATED_BODY()
public:
	ANPC_DrJoe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//���� ���ϰ� �;� �մϴ�. ��ũ�� ���ݴϴ�
	void WannaTalkTo();
	
	//���� �̴ϴ�. ���� OtherPlayer�� ���� widget�� ���޵Ǿ�� �մϴ�
	void TalkTo();
protected:

	
protected:
	//���� ���� �󸶳� ��ȭ�� �ߴ��� ī�����մϴ�
	UPROPERTY(VisibleAnywhere, Category = "Communication")
	int32 TalkingCount;
	//���� �ɷ��� �ϴ� ���. Camera Pawn�� �ȴ�
	UPROPERTY(VisibleAnywhere, Category = "Communication")
	TWeakObjectPtr<APawn>OtherPlayer;
};
