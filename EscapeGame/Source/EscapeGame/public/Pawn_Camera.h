// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Pawn.h"

#include "Engine/DataTable.h"

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
	void ListenTalk(TWeakObjectPtr<ACharacter> Talker,FText Diagram);
	//말을 걸어오기 시작할 때 호출합니다
	void StartListenTo(TWeakObjectPtr<ACharacter>Talker);
	UFUNCTION(BlueprintCallable)
	void OnNextClicked();
	UFUNCTION(BlueprintCallable)
	void OnPrevClicked();

private:
	//게임이 시작되면 스캔해서 찾아냅니다.
	void findTalkers();

private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* Cam;
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;
	//Array of Talkers. 
	UPROPERTY(VisibleAnywhere, Category = "DialogueInfo")
		TArray<TWeakObjectPtr<ACharacter>>a_Talkers;
	
	UPROPERTY(VisibleAnywhere, Category = "DialogueInfo", meta = (AllowPrivateAccess = "true"))
		class UDataTable* dialogueTable;

};


USTRUCT(BlueprintType)
struct FDialogueTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	//대사 내용
	UPROPERTY(VisibleAnywhere)
		FText Dialogue;
	//화자
	UPROPERTY(VisibleAnywhere)
		FText Talker;
	//몇 번재 Act인지
	UPROPERTY(VisibleAnywhere)
		int32 n_Act;
	//몇 번째 대사인지
	UPROPERTY(VisibleAnywhere)
		int32 Line;
};