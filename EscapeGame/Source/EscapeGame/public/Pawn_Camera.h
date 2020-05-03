// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Pawn.h"

#include "Engine/DataTable.h"

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
	void ListenTalk(TWeakObjectPtr<ACharacter> Talker,FText Diagram);
	//���� �ɾ���� ������ �� ȣ���մϴ�
	void StartListenTo(TWeakObjectPtr<ACharacter>Talker);
	UFUNCTION(BlueprintCallable)
	void OnNextClicked();
	UFUNCTION(BlueprintCallable)
	void OnPrevClicked();

private:
	//������ ���۵Ǹ� ��ĵ�ؼ� ã�Ƴ��ϴ�.
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
	//��� ����
	UPROPERTY(VisibleAnywhere)
		FText Dialogue;
	//ȭ��
	UPROPERTY(VisibleAnywhere)
		FText Talker;
	//�� ���� Act����
	UPROPERTY(VisibleAnywhere)
		int32 n_Act;
	//�� ��° �������
	UPROPERTY(VisibleAnywhere)
		int32 Line;
};