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

	//대상과 말하고 싶어 합니다. 링크만 해줍니다
	void WannaTalkTo();
	
	//말을 겁니다. 말은 OtherPlayer를 통해 widget에 전달되어야 합니다
	void TalkTo();
protected:

	
protected:
	//지금 상대와 얼마나 대화를 했는지 카운팅합니다
	UPROPERTY(VisibleAnywhere, Category = "Communication")
	int32 TalkingCount;
	//말을 걸려고 하는 대상. Camera Pawn이 된다
	UPROPERTY(VisibleAnywhere, Category = "Communication")
	TWeakObjectPtr<APawn>OtherPlayer;
};
