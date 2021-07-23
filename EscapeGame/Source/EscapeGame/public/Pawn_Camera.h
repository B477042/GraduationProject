// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Pawn.h"
//#include "NPCCharacter.h"
#include "Engine/DataTable.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

#include "Pawn_Camera.generated.h"



USTRUCT(BlueprintType)
struct FDialogueTableRow : public FTableRowBase
{
	GENERATED_BODY()
	public:
	//��� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FString Dialogue;
	//ȭ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FText Talker;
	//�� ���� Act����, �̻��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	int32 n_Act;
	//�� ��° �������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	int32 Line;
};

/*
	��ȭ�� �ϴ� ����� �Կ��ϴ� pawn
	��ȭ�� �Ͼ�� ��ũ��Ʈ�� ���⿡ ����ǰ�
	next prev ��ư�� ���� ��ȣ�ۿ�����
	�Ѿ�� ��ȭ�� ���⼭ ó���Ѵ�.
	��ư�� ������ �̺�Ʈ�� ����� �Ǵ� ĳ���Ϳ� �������� �ش�.


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
	void AddTalkingActor(TWeakObjectPtr<class ANPCCharacter> Talker);
	//���� �ɾ���� ������ �� ȣ���մϴ�
	void StartListenTo(TWeakObjectPtr<class ANPCCharacter>Talker);
	
	//���ǵ� �� ������ ��������Ʈ�� ����Ѵ�
	UFUNCTION(BlueprintCallable)
	void OnNextClicked();
	//���ǵ� �� ������ ��������Ʈ�� ����Ѵ�
	UFUNCTION(BlueprintCallable)
	void OnPrevClicked();

private:
	
	//��Ȳ�� �´� ��ȭ ����� �ҷ��ɴϴ�.
	void loadDialogue();
	//ó�� ȭ�鿡 ��ﶧ�� ����Ѵ�
	void startTalk();
	void nextLog();
	void prevLog();
	//���� ����ؾߵ� ���� ���
	void printLog();
	void registDelegateToWidget();
	class UDialogueWidget* getWidget();
private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* Cam;
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;
	//Array of Talkers. 
	UPROPERTY(VisibleAnywhere, Category = "DialogueInfo")
	TArray<TWeakObjectPtr<ANPCCharacter>  >a_Talkers;
	UPROPERTY(VisibleAnywhere, Category = "DialogueInfo", meta = (AllowPrivateAccess = "true"))
	class UDataTable*  dialogueTable;
	/*UPROPERTY(VisibleAnywhere, Category = "DialogueInfo", meta = (AllowPrivateAccess = "true"))
		TArray< class UDataTable* > dialogueTable;*/
	UPROPERTY(VisibleAnywhere, Category = "DialogueInfo", meta = (AllowPrivateAccess = "true"))
		TArray< FDialogueTableRow>dialogues;
	//���� ������ n_Act�� �����Ѵ�
	//static int n_Act;
	//��ȭ�� Log�� ����� �� ���� ����. ��ȭ���� ó�� ���� 0���� �ȴ�
	UPROPERTY(Transient, VisibleAnywhere, Category = "DialogueInfo")
	uint32 c_Talk;
	//���� ���̾�α��� ��� �� ��� ����. 6���̸� 5�� �� ���̴�
	UPROPERTY(Transient, VisibleAnywhere, Category = "DialogueInfo")
	uint32 maxLine;

	bool bIsDelegateRegist;
	
};


